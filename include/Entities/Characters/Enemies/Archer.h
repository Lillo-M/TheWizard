#pragma once

#include "Enemy.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "../../../GraphicElements/Animation.h"
#include "../../Arrow.h"
#define MULT 60

namespace Entities
{
    namespace Characters
    {
        namespace Enemies
        {
            class Archer : public Enemy
            {
            private:
                std::vector<Arrow*> aShots;
                static sf::Texture* texture; 
                GraphicElements::Animation animation;
            public:
                Archer(const sf::Vector2f pos = sf::Vector2f(0, 0));
                ~Archer();
                void Update();
                void Attack(const bool b);
                std::vector<Arrow*>* getShots();
            };
        }
    }
}