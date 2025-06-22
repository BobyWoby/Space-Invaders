#include "Game.h"
#include "Enemy.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_keycode.h"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include "Bullet.h"
#include <ctime>

Game *Game::instance = 0;
void Game::processEvents(SDL_Event *event){
    if (event->type == SDL_EVENT_QUIT)
        running = false;
    if (event->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event->window.windowID == SDL_GetWindowID(window))
        running = false;
    if(event->type == SDL_EVENT_KEY_DOWN){
        SDL_Keycode keycode = event->key.key;
        switch(keycode){
            case SDLK_ESCAPE:
                running = false;
                break;
            case SDLK_A:
                if(state == RUNNING)
                    player.move(deltaTime, true);
                break;
            case SDLK_D:
                if(state == RUNNING)
                    player.move(deltaTime, false);
                break;
            case SDLK_SPACE:
                if(state == RUNNING)
                    player.shoot(entities);
                break;
        }
    }
}
void Game::detectCollisions(){
    for(int i = entities.size() - 1; i >= 0; i--){
        auto entity  = entities.at(i);
        for(int j = entities.size()-1; j>=0;j--){
            if(i == j || entity->id == entities.at(j)->id) continue;
            if(entity->detectCollision(*entities.at(j))){
                entity->hp -= entities.at(j)->damage;
            }
        }

        entity->move(deltaTime);

        if(entity->id ==  ENEMY && entity->y >= player.y){
            player.hp -= entity->damage;
            entity->hp = 0;
        }
        if(entity->hp <=  0 || (entity->wallCollision && entity->atWall(windowWidth, windowHeight))){
            delete entity;
            entities.erase(entities.begin() + i);
        }
    }
}

void Game::render(){
    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if(showDemo){
        ImGui::ShowDemoWindow(&showDemo);
    }

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    entityWindow();

    // 3. Show another simple window.
    if (showOtherWindow)
    {
        ImGui::Begin("Another Window", &showOtherWindow);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            showOtherWindow = false;
        ImGui::End();
    }

    // Rendering
    ImGui::Render();
    SDL_SetRenderScale(renderer, io->DisplayFramebufferScale.x, io->DisplayFramebufferScale.y);
    // SDL_SetRenderDrawColorFloat(renderer, clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
    SDL_RenderPresent(renderer);
}

void Game::update()
{
    
    Uint64 now = SDL_GetTicks();
    deltaTime = (double)((now - lastTick)) / 1000.0; // seconds
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL3_ProcessEvent(&event);
        processEvents(&event);
    }

    // update physics and stuff here
    detectCollisions();
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0 ,255);
    SDL_RenderClear(renderer);

    // render other stuff here
    for(auto entity : entities){
        entity->render(renderer);
    }

    player.render(renderer);
    player.lastShot += deltaTime;
    if(player.hp <= 0){
        state = LOSE;
    }
    
    render();

    // update the lastTick
    lastTick = now;
}

Game::Game(){
    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("Couldn't Init SDL: %s", SDL_GetError());
    }
    SDL_CreateWindowAndRenderer("Space Invaders", windowWidth, windowHeight, SDL_WINDOW_RESIZABLE, &window, &renderer);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(window);
    initImGui();
    player = Player(renderer, 5000.0);
    reset();
}

void Game::reset(){
    for(auto entity : entities){
        delete entity;
    }
    entities.clear();
    for(int i = 0 ; i < enemyCount;  i++){
        float x = 300 + (windowWidth /  2 + spacing * (i % 10 - enemyCount / 2)) % (10 * spacing);
        float y = 100 + spacing * (int)(i / 10);
        entities.push_back(new Enemy(x, y));
    }
    player.hp = 100;
    state = RUNNING;
}

// ImGui Stuff Here
void Game::initImGui(){
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO(); (void)io;

    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch
    ImGui::StyleColorsDark();

    float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    SDL_WindowFlags window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;

    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
    style.FontScaleDpi = main_scale * 2;        // Set initial font scale. (using io.ConfigDpiScaleFonts=true makes this unnecessary. We leave both here for documentation purpose)
    style.FontSizeBase = 20.0f;
    font = io->Fonts->AddFontFromFileTTF("/usr/share/fonts/JetBrainsMono/JetBrainsMonoNerdFont-Regular.ttf");
    IM_ASSERT(font != nullptr);
    ImGui::PushFont(font);

    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

}

void Game::entityWindow(){
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Dev Panel");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("Player HP: %f", player.hp);               // Display some text (you can use a format strings too)
    ImGui::Text("Number of NPCs: %zu", entities.size());               // Display some text (you can use a format strings too)
    // ImGui::Checkbox("Demo Window", &showDemo);      // Edit bools storing our window open/close state
    // ImGui::Checkbox("Another Window", &showOtherWindow);

    ImGui::InputInt("Number of enemies", &enemyCount);
    ImGui::SliderFloat("Player Speed", &player.speed, 0.0f, 10000.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::SliderFloat("Player Attack Speed", &player.attackSpeed, 0.0f, 100.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                                                                                             // ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

    if (ImGui::Button("Reset"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        reset();
    // ImGui::SameLine();
    // ImGui::Text("counter = %d", counter);

    ImGui::Text("deltaTime: %f", deltaTime);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
    ImGui::End();

}

Game *Game::getInstance(){
    if(instance == 0){
        instance = new Game;
    }
    return instance;
}

Game::~Game(){
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    for(auto entity : entities){
        delete entity;
    }
    delete instance;
}
