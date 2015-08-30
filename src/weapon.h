#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Weapon
{
private:
	int id;
	std::string name;
	int damage;
	int ammo;

	float delay;
	sf::Clock fire_timer;

	sf::Texture txr;
	sf::Sprite sprite;
public:
	void init(std::string, int, float, int);

	std::string get_name() { return this->name; }
	int get_dmg() { return this->damage; }
	int get_ammo() { return this->ammo; }
	void add_ammo(int a) { this->ammo += a; }
	float get_delay() { return this->delay; }
	sf::Clock& get_timer() { return this->fire_timer; }
	void set_id(int id) { this->id=id; }
	int get_id() { return this->id; }

	enum WeaponEnum
	{
		PISTOL = 0,
		SHOTGUN = 1,
		M4A1 = 2
	} weapon_list;
};

#endif // WEAPON_H
