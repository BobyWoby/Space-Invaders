#pragma once
#include "Entity.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"

class Enemy : public Entity{
    public:
        float iX, iY;
        Enemy();
        Enemy(float x, float y);
        ~Enemy();
        void render(SDL_Renderer *renderer) override;
        void move(float dt) override;
        SDL_Texture *tex;
        SDL_Surface *surface;
        void loadImage(SDL_Renderer *renderer);

};

