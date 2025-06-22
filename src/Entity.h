#pragma once
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"

typedef enum EntityType{
    NONE,
    PLAYER,
    PROJECTILE,
    ENEMY
} EntityType;
class Entity{
public:
    EntityType id = NONE;
    float hp = 100; 
    float damage = 0; 
    float speed = 1000.0;
    float x, y, w, h; // Bounding box, x and y are the top left
    bool wallCollision = true;
    bool damagesPlayer = false;
    double accumulatingTime = 0;

    bool detectCollision(Entity &other);
    bool atWall(int windowWidth, int windowHeight);
    virtual void move(float dt){};
    virtual void render(SDL_Renderer *renderer){SDL_Log("Default Entity render called");};
};
