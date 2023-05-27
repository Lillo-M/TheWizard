#include "../include/Managers/CollisionManager.h"
#include <iostream>
Managers::CollisionManager::CollisionManager()
{
	Sentities = NULL;
	Dentities = NULL;
}

Managers::CollisionManager::~CollisionManager()
{
	Sentities = NULL;
	Dentities = NULL;
}

void Managers::CollisionManager::setSList(Math::List<Entities::Entity>& ents)
{
	Sentities = &ents;
}

void Managers::CollisionManager::setDList(Math::List<Entities::Entity>& ents)
{
	Dentities = &ents;
}

void Managers::CollisionManager::normalCollision(Entities::Entity* ent, float dist_x, float dist_y, float size_x, float size_y, ID id)
{
	/*float size_y = ent->getSize().y / 2 + getSize().y / 2;
	float size_x = ent->getSize().x / 2 + getSize().x / 2;
	float dist_y = ent->getPosition().y - Position.y;
	float dist_x = ent->getPosition().x - Position.x;*/
	if (abs(dist_x) - size_x > abs(dist_y) - size_y) // retirar ABS
	{
		if (dist_x > 0)
		{
			ent->setPosition( ent->getPosition().x + dist_x - size_x , ent->getPosition().y);
			if (ent->getVelocity().x > 0)
				ent->setVelocity( 0, ent->getVelocity().y);
		}
		if (dist_x < 0)
		{
			ent->setPosition( ent->getPosition().x + dist_x + size_x , ent->getPosition().y);
			if (ent->getVelocity().x < 0)
				ent->setVelocity( 0, ent->getVelocity().y);
		}
	}
	else
	{
		if (dist_y > 0)
		{
			ent->setPosition( ent->getPosition().x, ent->getPosition().y + dist_y - size_y);
			if(id == ID::obstacle || id == ID::player)ent->setVelocity(ent->getVelocity().x,  0);
			if(id == ID::obstacle || id == ID::player)ent->setGrounded(true);
		}
		if (dist_y < 0)
		{
			ent->setPosition( ent->getPosition().x, ent->getPosition().y + size_y + dist_y);
			ent->setVelocity(ent->getVelocity().x,  0);
		}
	}
}


void Managers::CollisionManager::Manage()
{
	float dist_x = 0;
	float dist_y = 0;
	float dx = 0;
	float dy = 0;
	Math::EntityTList::Iterator Iterator_i;
	Math::EntityTList::Iterator Iterator_j;
	int i = 0;
	for (Iterator_i = Dentities->begin(); Iterator_i != Dentities->end(); Iterator_i++)
	{
		if(Iterator_i->getID() != ID::obstacle)
		{
			if(Iterator_i->getID() == ID::player || Iterator_i->getID() == ID::enemy)
			{	if(!static_cast<Entities::Characters::Character*>(*Iterator_i)->getAlive())
					continue;
			}
			else
				if(static_cast<Entities::Projectile*>(*Iterator_i)->getCollided())
					continue;
		}
		Iterator_j = Iterator_i;
		Iterator_j++;
		for (Iterator_j; Iterator_j != Dentities->end(); Iterator_j++)
		{
			if(Iterator_j->getID() != ID::obstacle)
			{
				if(Iterator_j->getID() == ID::player || Iterator_j->getID() == ID::enemy)
				{	
					if(!static_cast<Entities::Characters::Character*>(*Iterator_j)->getAlive())
						continue;
				}
				else
					if(static_cast<Entities::Projectile*>(*Iterator_j)->getCollided())
						continue;
			}
			dist_x = Iterator_j->getPosition().x - Iterator_i->getPosition().x;
			dist_y = Iterator_j->getPosition().y - Iterator_i->getPosition().y;
			dx = Iterator_i->getSize().x / 2 + Iterator_j->getSize().x / 2;
			dy = Iterator_i->getSize().y / 2 + Iterator_j->getSize().y / 2;

			
			if (abs(dist_x) < dx && abs(dist_y) < dy)
			{
				normalCollision(*Iterator_i, dist_x, dist_y, dx, dy, Iterator_j->getID());
				normalCollision(*Iterator_j, -dist_x, -dist_y, dx, dy, Iterator_i->getID());
				Iterator_i->OnCollision(*Iterator_j);
				Iterator_j->OnCollision(*Iterator_i);
			}
		}
		for (Iterator_j = Sentities->begin(); Iterator_j != Sentities->end(); Iterator_j++)
		{

			dist_x = Iterator_j->getPosition().x - Iterator_i->getPosition().x;
			dist_y = Iterator_j->getPosition().y - Iterator_i->getPosition().y;
			dx = Iterator_i->getSize().x / 2 + Iterator_j->getSize().x / 2;
			dy = Iterator_i->getSize().y / 2 + Iterator_j->getSize().y / 2;
			if (abs(dist_x) < dx && abs(dist_y) < dy)
			{
				normalCollision(*Iterator_i, dist_x, dist_y, dx, dy, Iterator_j->getID());
				Iterator_i->OnCollision(*Iterator_j);
			}
		}
	}
}
