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

void Mob::handle_events(sf::Event *event)
{
	if(!removed)
	{}
}

void Mob::update(sf::Time deltaTime)
{
	if(hp <= 0){
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
