#include "Bullet.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3_image/SDL_image.h"

float Bullet::bulletWidth = 10;
float Bullet::bulletHeight = 100;

Bullet::Bullet(){
    id = PROJECTILE;
    this->w = bulletWidth;
    this->h = bulletHeight;
    this->hp =  1;
}

Bullet::Bullet(float x, float y){
    id = PROJECTILE;
    this->x = x;
    this->y = y;
    this->damage = 20;
    this->hp =  1;
    this->w = bulletWidth;
    this->h = bulletHeight;

}

Bullet::Bullet(float x, float y, float s){
    id = PROJECTILE;
    this->x = x;
    this->y = y;
    this->speed = s;
    this->damage = 20;
    this->hp =  1;
    this->w = bulletWidth;
    this->h = bulletHeight;
}

void Bullet::render(SDL_Renderer *renderer) {
    // SDL_SetRenderTarget(renderer, NULL);
    //Set texture position
    SDL_FRect dstRect{ x, y, static_cast<float>(w), static_cast<float>(h) };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &dstRect);
}

Bullet::~Bullet(){

}

void Bullet::move(float dt){
    if(up){
        y -= speed * dt;
    } else {
        y -= speed * dt;
    }
}


void Bullet::loadImage(SDL_Renderer *renderer){
    SDL_Surface *surface = IMG_Load("assets/player.png");
    if(surface == nullptr){
        SDL_Log("Error loading image: %s", SDL_GetError());
    }

    // tex = SDL_CreateTextureFromSurface(renderer, surface);
    // if(tex == nullptr){
    //     SDL_Log("Error loading texture: %s", SDL_GetError());
    // }
    // w = surface->w;
    // h = surface->h;
    SDL_DestroySurface(surface);
}
