#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <SFML/Graphics.hpp>

class Weapon
{
private:
	int damage;
	int ammo;
	float firetime;
	std::string name;
	sf::Texture txr;
	sf::Sprite sprite;
public:
	void init(std::string, int, int);

	int get_dmg() { return this->damage; }
	void add_ammo(int a) { this->ammo += a; }
};

#endif // WEAPON_H
