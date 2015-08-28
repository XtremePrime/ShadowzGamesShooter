#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "mob.h"
#include "../gameobject.hpp"
#include "../levels/tile.h"
#include "../weapon.h"

class Player : public Mob
{
private:
	sf::Vector2f acceleration;
	int score = 0;
	Weapon weapon;

	std::map<std::string, sf::Keyboard::Key> keys;
	bool is_standard_movement;
public:
    int hp=100;
    bool is_dead = false;
    int x, y, vx, vy, lx, ly;
	void init(GameObject* gameobj, int, int, int, int);
	void init(int, int, int, int);
	void handle_events(sf::Event*);
	void render(sf::RenderWindow*);
	void update(sf::Time);
	void move(sf::Time);
	bool can_move(Tile* tile);
	void move2(int, int, sf::Time);
    bool was_hurt (Player p, Mob* mob);

	int get_x(){return this->x;}
	int get_y(){return this->y;}
	void set_x(int xx){this->x = xx;}
	void set_y(int yy){this->y = yy;}
	int get_lx(){return this->lx;}
	int get_ly(){return this->ly;}
	void set_lx(int xx){this->lx = xx;}
	void set_ly(int yy){this->ly = yy;}
	int get_vx(){return this->vx;}
	int get_vy(){return this->vy;}
	sf::Keyboard::Key get_key(std::string key) { return keys[key]; }
	void set_key(std::string key, sf::Keyboard::Key val) { keys[key] = val; }
	int get_score() { return this->score; }
	void update_score(int score) { this->score += score; }
	bool get_death() { return this->is_dead; }
	Weapon& get_weapon() { return this->weapon; }
	void create_weapon(std::string name, int ammo, int dmg) { this->weapon.init(name, ammo, dmg); }
	void set_weapon(int id);
};

#endif // PLAYER_H
