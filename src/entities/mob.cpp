#include "mob.h"

#include <iostream>
#include <cmath>



Mob::Mob()
{

}

Mob::Mob(int x, int y, int w, int h)
{
    init(x,y,w,h);
}

Mob::~Mob()
{
    //TODO
}

void Mob::init(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->health = 100;
	texture.loadFromFile("res/models/enemymodel.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, w, h));
	sprite.rotate(-90);
	// sprite.setSize(sf::Vector2f(w, h));
	sprite.setPosition(sf::Vector2f(x, y));
	sprite.setOrigin(w/2, h/2);
	// vx = vy = 0;

	this->bbox = sprite.getGlobalBounds();
}

void Mob::move(int xp, int yp)
{
     if(x != xp)
                x += x-xp;

     if(y != yp)
                y += y-yp;


	sprite.setPosition(sf::Vector2f(x, y));


   /* //- Set direction
	if(y == -1)
		dir = Direction::UP;
	else if(y == 1)
		dir = Direction::DOWN;
	if(x == -1)
		dir = Direction::LEFT;
	else if(x == 1)
		dir = Direction::RIGHT;


*/
}

void Mob::handle_events(sf::Event *event)
{
	if(!removed)
	{}
}

void Mob::update(sf::Time deltaTime)
{
	if(health <= 0){
		remove();
	}
	this->bbox = sprite.getGlobalBounds();
}

void Mob::render(sf::RenderWindow *win)
{
	if(!removed)
	{
		win->draw(sprite);
	}
}
