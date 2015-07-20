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
	bool is_oob(int, int);
	void init(std::string);
	void handle_events(sf::Event*);
	void render(sf::RenderWindow*, int, int, int, int);
	void update(sf::Time);

	Tile* get_tile(int, int);
	sf::View& get_view() { return this->view; }
	sf::Vector2u& get_map_size() { return this->map_size; }
};

#endif // LEVEL_H
