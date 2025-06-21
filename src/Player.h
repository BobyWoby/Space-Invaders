#include "Entity.h"
#include "SDL3/SDL_render.h"
#include "Bullet.h"
#include <memory>
#include <vector>

class Player : public Entity {
    public:
        float bulletSpeed = 2000;
        uint16_t numBullets = 1; // number of bullets per shot

        SDL_Texture *tex = nullptr;
        Player(SDL_Renderer *renderer, float playerSpeed);
        ~Player();
        Player();

        void render(SDL_Renderer *renderer) override;
        void move(float dt, bool left);
        inline void move(float dt) override {};
        void loadImage(SDL_Renderer *renderer);

        void shoot(std::vector<Entity *> &entities);
};
