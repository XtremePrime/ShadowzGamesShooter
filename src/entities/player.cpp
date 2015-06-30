#include "player.h"

#include <cmath>

#define RADIAN (3.14159265 / 180.)

void Player::init(int xx, int yy)
{
	this->x = xx;
	this->y = yy;
	sprite.setSize(sf::Vector2f(xx, yy));
	sprite.setFillColor(sf::Color::White);
	sprite.setPosition(sf::Vector2f(xx, yy));
	vx = vy = 0;
}

void Player::render(sf::RenderWindow *win)
{
	win->draw(sprite);
}

void Player::move(sf::Time dt)
{
    vx = vy = 0;
    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    // 	sprite.rotate(-2);
    // else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    // 	sprite.rotate(2);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        vx += SPEED * sin(sprite.getRotation() * RADIAN);
        vy -= SPEED * cos(sprite.getRotation() * RADIAN);
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        vx -= SPEED * sin(sprite.getRotation()* RADIAN);
        vy += SPEED * cos(sprite.getRotation()* RADIAN);
    }
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		vx -= SPEED * cos(sprite.getRotation()* RADIAN);
		vy -= SPEED * sin(sprite.getRotation()* RADIAN);
	}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		vx += SPEED * cos(sprite.getRotation() * RADIAN);
		vy += SPEED * sin(sprite.getRotation() * RADIAN);
	}

	x += vx * dt.asSeconds();
	y += vy * dt.asSeconds();
	sprite.setPosition(sf::Vector2f(x, y));
}

void Player::update(sf::Time deltaTime)
{
	move(deltaTime);
}