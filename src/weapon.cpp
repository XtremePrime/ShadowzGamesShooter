#include "weapon.h"

void Weapon::init(std::string name, int ammo, int damage)
{
	this->name = name;
	this->ammo = ammo;
	this->damage = damage;
}