#include "mob.h"

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#define RADIAN (3.14159265 / 180.)



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
	this->health = 10;
	texture.loadFromFile("res/models/devtest/default.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, w, h));
	sprite.rotate(-90);
	// sprite.setSize(sf::Vector2f(w, h));
	sprite.setPosition(sf::Vector2f(x, y));
	sprite.setOrigin(w/2, h/2);
	// vx = vy = 0;

	rect.setPosition(sf::Vector2f(x, y));
	rect.setFillColor(sf::Color::Red);
	// rect.setOutlineColor(sf::Color::Black);
	// rect.setOutlineThickness(2.0f);
	rect.setSize(sf::Vector2f(w, h));
	rect.setOrigin(w/2, h/2);


	this->bbox = sprite.getGlobalBounds();
}

bool Mob::can_move(Tile* tile)
{
	if(!tile->can_pass())
		return false;
	return true;
}

void Mob::move(sf::Time dt)
{
	vx = vy = 0;

	#define RADIAN (3.14159265 / 180.)

	vx -= speed * cos(sprite.getRotation() * RADIAN);
    vy -= speed * sin(sprite.getRotation() * RADIAN);

    #undef RADIAN
}

void Mob::move2(int xa, int ya, sf::Time dt, int state)
{
	switch(state)
	{
		case 0:
			this->x += (xa) * dt.asSeconds();
			this->y += (ya) * dt.asSeconds();
		break;
		case 1:
			this->x += (xa) * dt.asSeconds();
		break;
		case 2:
			this->y += (ya) * dt.asSeconds();
		break;
	}


	// rect.setPosition(sf::Vector2f(x, y));
	sprite.setPosition(sf::Vector2f(x, y));
}



void Mob::handle_events(sf::Event *event)
{
	if(!removed)
	{}
}

void Mob::update(sf::Time deltaTime)
{
	// std::cout << "Bbox: " << this->bbox.top << "," << this->bbox.left << "\n";
	if(health <= 0)
		remove();
	move(deltaTime);
	this->bbox = sprite.getGlobalBounds();
	// this->bbox = sprite.getGlobalBounds();
}

void Mob::render(sf::RenderWindow *win)
{
	if(!removed)
	{
		// std::cout << "Render!\n";
		win->draw(sprite);
		// win->draw(rect);
	}
}
