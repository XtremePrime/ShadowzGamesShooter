#include "mob.h"

Mob::Mob(sf::Vector2f c, int type)
{
    init(c, type);
}

void Mob::init(sf::Vector2f c, int type)
{
    switch(type){
    //to do

    }

    this->hp =  ;//?
    this->max_hp = ; //?
    this->dmg =  ;//?

}

bool Mob::hasCollision(Tile* tile)
{
	if(tile->may_pass() == true)
		return false;
	return true;
}
