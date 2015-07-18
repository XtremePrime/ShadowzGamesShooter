#ifndef LEVEL_H
#define LEVEL_H

#include "levelgen.h"
#include "tile.h"
#include "spawnpointlist.h"

class Level
{
private:
	LevelGen gen;
	sf::View view;
	sf::Vector2u map_size;
	int TOTAL_TILES;
	SpawnPointList splist;
public:
	void init(std::string);
	void handle_events(sf::Event*);
	void render(sf::RenderWindow*, int, int, int, int);
	void update(sf::Time);

	Tile* get_tile(int, int);
	sf::View& get_view() { return this->view; }
};

#endif // LEVEL_H