#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "mob.h"

class Player : public Mob
{
private:
	int x, y, vx, vy;
	// sf::RectangleShape rect;
public:
	void init(int, int);
	void init(int, int, int, int);
	void handle_events(sf::Event*);
	void render(sf::RenderWindow*);
	void update(sf::Time);
	void move(sf::Time);

	int get_x(){return this->x;}
	int get_y(){return this->y;}
	sf::Sprite& get_model() { return this->sprite; }
};

#endif // PLAYER_H