#ifndef BASICENEMY_H
#define BASICENEMY_H

#include "mob.h"
#include <string>
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <sstream>

class BasicEnemy : public Mob
{
private:
public:
    BasicEnemy();
	BasicEnemy(int, int, int, int, int, std::string);
	~BasicEnemy();
	void init(int x, int y, int w, int h, int sp, std::string path);
};

#endif // BASICENEMY_H
