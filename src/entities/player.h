#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "mob.h"
#include "../gameobject.hpp"
#include "../levels/tile.h"

class Player : public Mob
{
private:
	int x, y, vx, vy, lx, ly;
	sf::Vector2f acceleration;
	int score = 0;
	std::map<std::string, sf::Keyboard::Key> keys;
	bool is_standard_movement;
public:
	void init(GameObject* gameobj, int, int, int, int);
	void init(int, int, int, int);
	void handle_events(sf::Event*);
	void render(sf::RenderWindow*);
	void update(sf::Time);
	void move(sf::Time);
	bool can_move(Tile* tile);
	void move2(int, int, sf::Time);

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
};

#endif // PLAYER_H