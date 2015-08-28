#ifndef SPAWNPOINTLIST_H
#define SPAWNPOINTLIST_H

#include <string>
#include <fstream>
#include "spawnpoint.h"

class SpawnPointList
{
private:
	std::string path;
	std::vector<SpawnPoint*> splist;

	void load_file(std::string);
public:
	void init(std::string);

	std::vector<SpawnPoint*> get_list() { return this->splist; }
	SpawnPoint& get_sp(int idx){ return (*splist[idx]); }
	SpawnPoint* get_sp(int, int);
};

#endif // SPAWNPOINTLIST_H