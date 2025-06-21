#include  "Enemy.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3_image/SDL_image.h"
#include "imgui.h"
#include <cmath>

void Enemy::loadImage(SDL_Renderer *renderer){
    SDL_Surface *surface = IMG_Load("assets/enemy.png");
    if(surface == nullptr){
        SDL_Log("Error loading image: %s", SDL_GetError());
    }

    tex = SDL_CreateTextureFromSurface(renderer, surface);
    if(tex == nullptr){
        SDL_Log("Error loading texture: %s", SDL_GetError());
    }
    w = surface->w * 2;
    h = surface->h * 2;
    SDL_DestroySurface(surface);
}
void Enemy::render(SDL_Renderer* renderer){
    loadImage(renderer);

    SDL_SetRenderTarget(renderer, NULL);
    //Set texture position
    SDL_FRect dstRect{ x, y, static_cast<float>(w), static_cast<float>(h) };
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
    SDL_RenderTexture( renderer, tex, nullptr, &dstRect );

}

void Enemy::move(float dt){
    // SDL_Log("X: %f, Y:  %f", x, y);
    // x += 1 * (std::cos(dt));
    // y += .50 * (-std::sin(3 * dt) + 1);
    accumulatingTime += dt;
    x =  100 * (std::sin(accumulatingTime)) + iX;
    y =  50 * (std::cos(3 * accumulatingTime) + accumulatingTime) + iY;
}

Enemy::Enemy(){
    iX = 700, iY  = 64;
    surface =  IMG_Load("assets/enemy.png");
    if(surface == nullptr){
        SDL_Log("Error loading image: %s", SDL_GetError());
    }
    w = surface->w * 2;
    h = surface->h * 2;

    damagesPlayer = true;
}

Enemy::~Enemy(){
    SDL_DestroySurface(surface);
    SDL_DestroyTexture(tex);
}
