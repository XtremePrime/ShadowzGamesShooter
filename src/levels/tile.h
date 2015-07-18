#include "../entities/entity.h"

#ifndef TILE_H
#define TILE_H

class Tile
{
private:
	sf::Sprite sprite;
	
	int x, y;
	bool is_hazard = false;
	bool is_collidable = false;
	sf::FloatRect bbox;
public:
	const int SIZE = 32;

	// Tile(int, int, std::string);
	Tile(int, int, sf::Texture&);
	Tile(int, int, bool, sf::Texture&);
	// void init(int, int, std::string);
	void init(int xx, int yy, sf::Texture&);
	void render(sf::RenderWindow*);
	void update(sf::Time);

	bool can_pass(){ return !is_collidable; }
	int get_x(){return this->x*SIZE;}
	int get_y(){return this->y*SIZE;}
	sf::Vector2i get_coord(){return sf::Vector2i(this->x, this->y);}
	void set_x(int xx){this->x=xx;}
	void set_y(int yy){this->y=yy;}
	sf::FloatRect& get_bbox() { return this->bbox; }
};

#endif // TILE_H