#include "weapon.h"

void Weapon::init(std::string name, int ammo, float d = 0.1f, int damage = 1)
{
	this->name = name;
	this->ammo = ammo;
	this->delay = d;
	this->damage = damage;
}
