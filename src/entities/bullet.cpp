#include "bullet.h"

Bullet::Bullet(int x, int y, float angle, int dmg = 1)
{
	this->x = x;
	this->y = y;
	this->w = 0.4;
	this->h = 0.6;
	this->speed = 600;
	this->damage = dmg;

	texture.loadFromFile("res/models/bullet.png");
	sprite.setTexture(texture);
	sprite.setRotation(angle+90);
	sprite.setScale(sf::Vector2f(w, h));
	sprite.setPosition(sf::Vector2f(x, y));
	sprite.setOrigin(w/2, h/2);
}

void Bullet::init(int x, int y, int w, int h)
{

}

void Bullet::handle_events(sf::Event *event)
{
	if(!removed){}
}

void Bullet::update(sf::Time deltaTime)
{
	if(!removed)
	{
		move(deltaTime);
		if(traveldist >= 100)
			remove();
		this->bbox = sprite.getGlobalBounds();
	}
}

void Bullet::move(sf::Time dt)
{
	vx = vy = 0;

	#define RADIAN (3.14159265 / 180.)

	vx -= speed * sin(sprite.getRotation() * RADIAN);
    vy += speed * cos(sprite.getRotation() * RADIAN);

    #undef RADIAN

    x += vx * dt.asSeconds();
	y += vy * dt.asSeconds();

	sprite.setPosition(sf::Vector2f(x, y));

	traveldist++;
}

void Bullet::render(sf::RenderWindow *win)
{
	if(!removed)
	{
		win->draw(sprite);
	}
}
