#include "levelgen.h"
#include "tile.h"

#ifndef LEVEL_H
#define LEVEL_H

class Level
{
private:
	LevelGen gen;
	sf::View view;
	int xscroll=32;
	sf::Vector2u map_size;
	int TOTAL_TILES;
public:
	void init(std::string);
	void handle_events(sf::Event*);
	void render(sf::RenderWindow*, int, int);
	void update(sf::Time);

	Tile* get_tile(int, int);
};

#endif // LEVEL_H