#include "levelgen.h"
#include "tile.h"

#ifndef LEVEL_H
#define LEVEL_H

class Level
{
private:
	LevelGen gen;
public:
	void init(std::string);
	void handle_events(sf::Event*);
	void render(sf::RenderWindow*);
	void update(sf::Time);
};

#endif // LEVEL_H