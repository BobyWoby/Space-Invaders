#include "Player.h"
#include "Entity.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3_image/SDL_image.h"
#include <cstddef>
#include <memory>

Player::Player(SDL_Renderer *renderer, float playerSpeed){
    this->x = 1000;
    this->y = 1000;
    this->w = 50;
    this->h = 50;

    loadImage(renderer);
    speed = playerSpeed;
}

void Player::loadImage(SDL_Renderer *renderer){
    SDL_Surface *surface = IMG_Load("assets/player.png");
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

void Player::render(SDL_Renderer *renderer) {
    loadImage(renderer);
    SDL_SetRenderTarget(renderer, NULL);

    //Set texture position
    SDL_FRect dstRect{ x, y, static_cast<float>(w), static_cast<float>(h) };
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
    SDL_RenderTexture( renderer, tex, nullptr, &dstRect );
}

void Player::shoot(std::vector<Entity *> &entities){
    for(int i = 0; i < numBullets; i++){
        int xOffset = 2 * (i - (int)(numBullets / 2)) * Bullet::bulletWidth;
        Bullet *newBullet  = new Bullet(x + xOffset + this->w / 2 - Bullet::bulletWidth / 2 , y, bulletSpeed);
        entities.push_back(newBullet);
    }
}

Player::Player(){
    this->x = 1000;
    this->y = 1000;
    this->w = 50;
    this->h = 50;
    speed = 1000.0;
}

void Player::move(float dt, bool left){
    if(left){
        x -= (speed * dt);
        return;
    }else{
        x += (speed * dt);
        return;
    }
}


Player::~Player(){
    SDL_DestroyTexture(tex);
}
