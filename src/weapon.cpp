#include "weapon.h"

void Weapon::init(std::string name, int ammo, int damage)
{
	this->name = name;
	this->ammo = ammo;
	this->damage = damage;
}

Weapon& Weapon::operator=(WeaponEnum we)
{
	Weapon w;

	switch(we)
	{
		case 0:
		break;
		default:
		break;
	}
	return w;
}