#include "Bullet.h"
#include "SDL3/SDL_rect.h"

float Bullet::bulletWidth = 10;
float Bullet::bulletHeight = 100;

Bullet::Bullet(){
}

Bullet::Bullet(float x, float y){
    this->x = x;
    this->y = y;
    this->damage = 20;
}

Bullet::Bullet(float x, float y, float s){
    this->x = x;
    this->y = y;
    this->speed = s;
    this->damage = 20;
}

void Bullet::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_SetRenderTarget(renderer, NULL);

    SDL_FRect rect = SDL_FRect(x, y, w, h);
    SDL_RenderFillRect(renderer, &rect);
}

Bullet::~Bullet(){

}

void Bullet::move(float dt){
    if(up){
        y -= speed * dt;
    } else {
        y += speed * dt;
    }

}
