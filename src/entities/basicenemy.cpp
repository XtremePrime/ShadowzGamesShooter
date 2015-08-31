#include "basicenemy.h"

#define RADIAN (3.14159265 / 180.)

BasicEnemy::BasicEnemy()
{

}

BasicEnemy::BasicEnemy(int x, int y, int w, int h, std::string path)
{
    init(x,y,w,h,path);
}

BasicEnemy::~BasicEnemy()
{
    //TODO
}

void BasicEnemy::init(int x, int y, int w, int h, std::string path)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->speed = 125;
	this->damage = 1;
	this->health = 5;
	{
		std::ostringstream ss;
		ss << "res/models/";
		ss << path;
		ss << "/default.png";
		texture.loadFromFile(ss.str());
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, w, h));
	sprite.rotate(-90);
	// sprite.setSize(sf::Vector2f(w, h));
	sprite.setPosition(sf::Vector2f(x, y));
	sprite.setOrigin(w/2, h/2);
	// vx = vy = 0;

	this->bbox = sprite.getGlobalBounds();
}