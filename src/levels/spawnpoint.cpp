#include "spawnpoint.h"

SpawnPoint::SpawnPoint(int xx, int yy)
{
	this->xt = xx;
	this->yt = yy;
	this->x = (xt*32)+32/2;
	this->y = (yt*32)+32/2;
	this->active = true;
}

