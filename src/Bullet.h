#pragma once
#include "Entity.h"

class Bullet : public Entity{
    public:
        static float bulletWidth, bulletHeight; // set the bulletWidth and Height before everything else
        bool up = true;
        SDL_Texture *tex;



        Bullet();
        Bullet(float x, float y);
        Bullet(float x, float y, float s);
        ~Bullet();

        void render(SDL_Renderer *renderer) override;
        void move(float dt) override;
        void loadImage(SDL_Renderer *renderer);
};
