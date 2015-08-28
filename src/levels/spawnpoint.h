#ifndef SPAWNPOINT_H
#define SPAWNPOINT_H

#include <SFML/Graphics.hpp>
#include <iostream>

class SpawnPoint
{
private:
	int x, y;
	bool active = true;
public:
	SpawnPoint(int, int);
	~SpawnPoint(){}

	int get_x() { return this->x; }
	int get_y() { return this->y; }
	void activate(){ this->active = true; }
	void deactivate(){ this->active = false; }	
};

#endif // SPAWNPOINT_H