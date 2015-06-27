#include "tile.h"
#include <iostream>

#ifndef LEVELGEN_H
#define LEVELGEN_H

class LevelGen
{
private:
	std::vector<Tile*> tiles;
	std::string path;

	void set();
	bool is_color(sf::Color,uint8_t,uint8_t,uint8_t);
	bool is_alpha(sf::Color,uint8_t);
public:
	LevelGen(){}
	~LevelGen(){}
	void init(std::string);
	void generate_map();

	std::vector<Tile*> get_tiles() { return this->tiles; }
};

#endif // LEVELGEN_H