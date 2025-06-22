#pragma once
#include "Entity.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "SDL3/SDL.h"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include <ctime>
#include <memory>
#include <vector>

#include "Player.h"

typedef enum GameState {
    RUNNING,
    WIN,
    LOSE,
} GameState;

class Game{
    protected:
        Game();
    public:
        static Game *instance;

        //SDL Stuff
        int windowHeight = 1280, windowWidth = 1960;

        // ImGui Stuff
        bool running = true, showDemo = false, showOtherWindow = false;
        SDL_Window *window;
        SDL_Renderer *renderer;
        ImGuiIO *io;
        ImFont *font;

        // Entities
        int enemyCount = 10;
        Player player;
        float bulW, bulH; // the bullet dimensions
        std::vector<Entity *> entities; // non-player entities

        // Physics
        double deltaTime = 0;
        Uint64 lastTick = 0;

        int spacing = 100;

        GameState state =  RUNNING;

        static Game *getInstance();
        void reset();
        void processEvents(SDL_Event *event);

        void update();
        void render();
        void detectCollisions();
        void entityWindow();

        void initImGui();

        ~Game();
        
};
