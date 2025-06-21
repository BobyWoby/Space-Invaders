#include "SDL3/SDL_keycode.h"
#include <SDL3/SDL_events.h>
#include <iostream>
#include "Game.h"


int main(){
    SDL_Window* window;
    SDL_Renderer* renderer;
    Game *game = Game::getInstance();

    while(game->running){
        game->update();
    }
    return 0;
}
