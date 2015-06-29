#include "../entities/entity.h"

#ifndef TILE_H
#define TILE_H

class Tile
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	int x, y;
	bool is_hazard = false;
	bool is_collidable = false;
public:
	const int SIZE = 32;

	Tile(int, int, std::string);
	void init(int, int, std::string);
	void render(sf::RenderWindow*);
	void update(sf::Time);

	bool can_pass(){ return is_collidable; }
	int get_x(){return this->y;}
	int get_y(){return this->x;}
	void set_x(int xx){this->x=xx;}
	void set_y(int yy){this->y=yy;}
};

#endif // TILE_H