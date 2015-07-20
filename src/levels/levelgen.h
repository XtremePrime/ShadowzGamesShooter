#ifndef LEVELGEN_H
#define LEVELGEN_H

#include "tile.h"
#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "../texturemanager.h"

class LevelGen
{
private:
	std::vector<Tile*> tiles;
	std::string path;
	std::map<std::string, sf::Color*> custom_tiles;
	sf::Vector2u size;
	TextureManager txmgr;

	void set();
	bool is_color(sf::Color,uint8_t,uint8_t,uint8_t);
	bool is_alpha(sf::Color,uint8_t);
	void grab_custom_tiles();
public:
	void init(std::string);
	void generate_map();

	std::vector<Tile*> get_tiles() { return this->tiles; }
	Tile* get_tile(int idx) { return tiles[idx]; }
	sf::Vector2u get_map_size() { return this->size; }
};

#endif // LEVELGEN_H