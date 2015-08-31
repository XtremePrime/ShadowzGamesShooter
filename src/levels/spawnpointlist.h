#ifndef SPAWNPOINTLIST_H
#define SPAWNPOINTLIST_H

#include <string>
#include <fstream>
#include "spawnpoint.h"
#include <SFML/System.hpp>

class SpawnPointList
{
private:
	std::string path;
	std::vector<SpawnPoint*> splist;
	float delay = 0.5f;
	int spawn_count = 0;
	sf::Clock timer;

	void load_file(std::string);
public:
	~SpawnPointList(){cleanup();}
	void init(std::string);
	void cleanup();

	std::vector<SpawnPoint*> get_list() { return this->splist; }
	SpawnPoint& get_sp(int idx){ return (*splist[idx]); }
	SpawnPoint* get_sp(int, int);
	int get_spawn_count() { return this->spawn_count; }
	sf::Clock& get_timer() { return this->timer; }
};

#endif // SPAWNPOINTLIST_H