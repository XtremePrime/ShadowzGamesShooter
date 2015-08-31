#ifndef SPAWNPOINT_H
#define SPAWNPOINT_H

#include <SFML/Graphics.hpp>
#include <iostream>

class SpawnPoint
{
private:
	int x, y;
	int xt, yt;
	bool active = true;
public:
	SpawnPoint(int, int);
	~SpawnPoint(){}

	int get_x() { return this->x; }
	int get_y() { return this->y; }
	int get_xt() { return this->xt; }
	int get_yt() { return this->yt; }
	void activate(){ this->active = true; }
	void deactivate(){ this->active = false; }	
};

#endif // SPAWNPOINT_H