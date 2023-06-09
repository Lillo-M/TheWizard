#pragma once
#include "../Entity.h"
namespace Entities
{
    namespace Characters
    {
        class Character : public Entities::Entity
        {    
        public:
            Character(const sf::Vector2f pos = sf::Vector2f(0, 0), const sf::Vector2f size = sf::Vector2f(0, 0), ID id = ID::empty, int lves = 0);
            virtual ~Character();
            void operator--();
            virtual void Move() = 0;
            virtual void Attack(const bool b) = 0;
            virtual void Update() = 0;
            virtual void Draw() = 0;
            virtual void Save(std::ofstream& savefile) = 0;
            virtual void Load(std::ifstream& savefile) = 0;
            virtual void OnCollision(Entity *ent) = 0;
            const bool getAlive() const;
            virtual void Damage();
            virtual void Damage(bool b);
            virtual void Damage(int damage);
            void setAlive(bool alive);
            void setLives(int lives);
        protected:
            bool damaged;
            float timecont;
            int lives;
            bool alive;
        };
    }
}