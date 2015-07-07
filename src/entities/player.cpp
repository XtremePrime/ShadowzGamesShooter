#include "player.h"

#include <cmath>
#include <iostream>

#define RADIAN (3.14159265 / 180.)

void Player::init(int xx, int yy)
{

}

void Player::init(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->speed = 250;	

	texture.loadFromFile("res/models/playermodel.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, w, h));
	sprite.rotate(-90);
	// sprite.setSize(sf::Vector2f(w, h));
	sprite.setPosition(sf::Vector2f(x, y));
	sprite.setOrigin(w/2, h/2);
	vx = vy = 0;	

	this->bbox = sprite.getGlobalBounds();
}

void Player::handle_events(sf::Event *ev)
{

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

 //    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
 //        vx += speed * sin(sprite.getRotation() * RADIAN);
 //        vy -= speed * cos(sprite.getRotation() * RADIAN);
 //    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
 //        vx -= speed * sin(sprite.getRotation()* RADIAN);
 //        vy += speed * cos(sprite.getRotation()* RADIAN);
 //    }
	
	// if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
	// 	vx -= speed * cos(sprite.getRotation()* RADIAN);
	// 	vy -= speed * sin(sprite.getRotation()* RADIAN);
	// }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
	// 	vx += speed * cos(sprite.getRotation() * RADIAN);
	// 	vy += speed * sin(sprite.getRotation() * RADIAN);
	// }

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		vx -= speed * cos(sprite.getRotation() * RADIAN);
    	vy -= speed * sin(sprite.getRotation() * RADIAN);
	}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		vx += speed * cos(sprite.getRotation()* RADIAN);
    	vy += speed * sin(sprite.getRotation()* RADIAN);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		vx += speed * sin(sprite.getRotation() * RADIAN);
		vy -= speed * cos(sprite.getRotation() * RADIAN);
	}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		vx -= speed * sin(sprite.getRotation()* RADIAN);
		vy += speed * cos(sprite.getRotation()* RADIAN);
	}

	x += vx * dt.asSeconds();
	y += vy * dt.asSeconds();
	sprite.setPosition(sf::Vector2f(x, y));
}

void Player::update(sf::Time deltaTime)
{
	move(deltaTime);
	this->bbox = sprite.getGlobalBounds();
}