#include "Entity.h"
#include <cstdlib>

bool Entity::detectCollision(Entity& other){
    return this->x < other.x + other.w &&
        this->x + this->w > other.x &&
        this->y < other.y + other.h &&
        this->y + this->h > other.y;
}
