#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "mob.h"
#include "../gameobject.hpp"

class Player : public Mob
{
private:
	int x, y, vx, vy;
	std::map<std::string, sf::Keyboard::Key> keys;
	bool is_standard_movement;
public:
	void init(GameObject* gameobj, int, int, int, int);
	void init(int, int, int, int);
	void handle_events(sf::Event*);
	void render(sf::RenderWindow*);
	void update(sf::Time);
	void move(sf::Time);

	int get_x(){return this->x;}
	int get_y(){return this->y;}
	sf::Keyboard::Key get_key(std::string key) { return keys[key]; }
	void set_key(std::string key, sf::Keyboard::Key val) { keys[key] = val; }
};

#endif // PLAYER_H