#pragma once
#include "SDL3/SDL_render.h"

class Entity{
public:
    float hp = 100; 
    float damage = 0; 
    float speed = 1000.0;
    float x, y, w, h; // Bounding box, x and y are the top left

    bool detectCollision(Entity &other);
    virtual void move(float dt){};
    virtual void render(SDL_Renderer *renderer){};
};
