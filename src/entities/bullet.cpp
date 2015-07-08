#include "bullet.h"

Bullet::Bullet(int x, int y, float angle)
{
	this->x = x;
	this->y = y;
	this->w = 10;
	this->h = 20;
	this->speed = 600;

	rect.setRotation(angle+90);
	rect.setSize(sf::Vector2f(w, h));
	rect.setPosition(sf::Vector2f(x, y));
	rect.setOrigin(w/2, h/2);
	rect.setFillColor(sf::Color::Yellow);
}

void Bullet::init(int x, int y, int w, int h)
{

}

void Bullet::handle_events(sf::Event *event)
{

}

void Bullet::update(sf::Time deltaTime)
{
	move(deltaTime);
}

void Bullet::move(sf::Time dt)
{
	vx = vy = 0;

	#define RADIAN (3.14159265 / 180.)

	vx -= speed * sin(rect.getRotation() * RADIAN);
    vy += speed * cos(rect.getRotation() * RADIAN);

    #undef RADIAN

    x += vx * dt.asSeconds();
	y += vy * dt.asSeconds();

	rect.setPosition(sf::Vector2f(x, y));
}

void Bullet::render(sf::RenderWindow *win)
{
	win->draw(rect);
}