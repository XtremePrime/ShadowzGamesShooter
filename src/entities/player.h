#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player
{
private:
	int x, y, vx, vy;
	const int SPEED = 300;
	sf::RectangleShape sprite;
public:
	void init(int, int);
	void handle_events(sf::Event*);
	void render(sf::RenderWindow*);
	void update(sf::Time);
	void move(sf::Time);

	int get_x(){return this->x;}
	int get_y(){return this->y;}
};

#endif // PLAYER_H