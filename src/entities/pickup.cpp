#include "pickup.h"

Pickup::Pickup(int id, int x, int y, int w, int h)
{
	init(id,x,y,w,h);
}

void Pickup::init(int id, int x, int y, int w, int h)
{
	this->id = id;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;

	switch(this->id)
	{
		#define set(fp) this->texture.loadFromFile(fp);
		case PickupCodes::HEALTH:
			set("res/pickups/hp.png");
		break;
		case PickupCodes::SHOTGUN:
			set("res/pickups/shotgun.png");
		break;
		case PickupCodes::SMG:
			set("res/pickups/smg.png");
		break;
		#undef set
	}
	this->sprite.setTexture(texture);
	this->sprite.setOrigin(w/2, h/2);
	this->sprite.setPosition(sf::Vector2f(x, y));
	this->alive_timer.restart();
}

void Pickup::update(sf::Time deltaTime)
{
	this->bbox = sprite.getGlobalBounds();
}

void Pickup::render(sf::RenderWindow* window)
{
	if(!removed)
		window->draw(this->sprite);
}
