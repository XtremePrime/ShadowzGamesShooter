#include "mob.h"

#include <iostream>
#include <cmath>

Mob::Mob()
{
    //TODO
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
	rect.setSize(sf::Vector2f(w, h));
	rect.setFillColor(sf::Color::Red);
	rect.setPosition(sf::Vector2f(x, y));

	this->bbox = sprite.getGlobalBounds();
}

void Mob::handle_events(sf::Event *event)
{

}

void Mob::update(sf::Time deltaTime)
{
	this->bbox = sprite.getGlobalBounds();
}

void Mob::render(sf::RenderWindow *win)
{
	win->draw(rect);
}
