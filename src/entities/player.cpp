#include "player.h"

#include <cmath>
#include <iostream>
#include <SFML/System.hpp>
#include <ctime>

#define RADIAN (3.14159265 / 180.)

void Player::init(GameObject* gameobj, int x, int y, int w, int h)
{
	this->is_standard_movement = gameobj->is_standard_movement;
	init(x, y, w, h);
}

void Player::init(int x, int y, int w, int h)
{
	//- Init basic coords
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->lx = x;
	this->ly = y;
	vx = vy = 0;
	this->speed = 250;

	//- Init sprite
	texture.loadFromFile("res/models/player_1.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, w, h));
	sprite.rotate(-90);
	// sprite.setSize(sf::Vector2f(w, h));
	sprite.setPosition(sf::Vector2f(x, y));
	sprite.setOrigin(w/2, h/2);

	this->bbox = sprite.getGlobalBounds();

	//- Init keys
	keys["up"] = sf::Keyboard::W;
	keys["down"] = sf::Keyboard::S;
	keys["left"] = sf::Keyboard::A;
	keys["right"] = sf::Keyboard::D;
}

void Player::handle_events(sf::Event *event)
{
	sf::Event ev = *event;
	if(ev.type == sf::Event::KeyPressed)
	{
		switch(ev.key.code)
		{
			default:
			break;
		}
	}
}

void Player::render(sf::RenderWindow *win)
{
	win->draw(sprite);
}

bool Player::can_move(Tile* tile)
{
	if(!tile->can_pass())
		return false;
	return true;
}

void Player::move(sf::Time dt)
{
    vx = vy = 0;

    if(!is_standard_movement)
    {
		if(sf::Keyboard::isKeyPressed(keys["up"])){
			vx -= speed * cos(sprite.getRotation() * RADIAN);
    		vy -= speed * sin(sprite.getRotation() * RADIAN);
		}else if(sf::Keyboard::isKeyPressed(keys["down"])){
			vx += speed * cos(sprite.getRotation()* RADIAN);
    		vy += speed * sin(sprite.getRotation()* RADIAN);
		}
		if(sf::Keyboard::isKeyPressed(keys["right"])){
			vx += speed * sin(sprite.getRotation() * RADIAN);
			vy -= speed * cos(sprite.getRotation() * RADIAN);
		}else if(sf::Keyboard::isKeyPressed(keys["left"])){
			vx -= speed * sin(sprite.getRotation()* RADIAN);
			vy += speed * cos(sprite.getRotation()* RADIAN);
		}
	}else{
		if(sf::Keyboard::isKeyPressed(keys["up"])){
			vy -= speed;
			// vy -= 1;
		}else if(sf::Keyboard::isKeyPressed(keys["down"])){
			vy += speed;
			// vy += 1;
		}
		if(sf::Keyboard::isKeyPressed(keys["right"])){
			vx += speed;
			// vx += 1;
		}else if(sf::Keyboard::isKeyPressed(keys["left"])){
			vx -= speed;
			// vx -= 1;
		}
	}
}

//- DEPRECATED
/*void Player::move(sf::Time dt)
{
    vx = vy = 0;

    if(!is_standard_movement)
    {
		if(sf::Keyboard::isKeyPressed(keys["up"])){
			vx -= speed * cos(sprite.getRotation() * RADIAN);
    		vy -= speed * sin(sprite.getRotation() * RADIAN);
		}else if(sf::Keyboard::isKeyPressed(keys["down"])){
			vx += speed * cos(sprite.getRotation()* RADIAN);
    		vy += speed * sin(sprite.getRotation()* RADIAN);
		}
		if(sf::Keyboard::isKeyPressed(keys["right"])){
			vx += speed * sin(sprite.getRotation() * RADIAN);
			vy -= speed * cos(sprite.getRotation() * RADIAN);
		}else if(sf::Keyboard::isKeyPressed(keys["left"])){
			vx -= speed * sin(sprite.getRotation()* RADIAN);
			vy += speed * cos(sprite.getRotation()* RADIAN);
		}
	}else{
		if(sf::Keyboard::isKeyPressed(keys["up"])){
			vy -= speed;
		}else if(sf::Keyboard::isKeyPressed(keys["down"])){
			vy += speed;
		}
		if(sf::Keyboard::isKeyPressed(keys["right"])){
			vx += speed;
		}else if(sf::Keyboard::isKeyPressed(keys["left"])){
			vx -= speed;
		}
	}

	return sf::Vector2f(vx, vy);
	// x += vx * dt.asSeconds();
	// y += vy * dt.asSeconds();
	// sprite.setPosition(sf::Vector2f(x, y));
}*/

void Player::move2(int xa, int ya, sf::Time dt)
{
	this->x += (xa) * dt.asSeconds();
	this->y += (ya) * dt.asSeconds();
	sprite.setPosition(sf::Vector2f(x, y));
}

/*bool was_hurt (Mob* mob){
if(mob->intersects (this)) return true;
return false;

}
*/



void Player::update(sf::Time deltaTime)
{
	move(deltaTime);
	/*if (was_hurt(p , Mob)== true){
        bool hurt= true;
        sf::Clock clock;
        sf::Clock elapsed;
        float time = clock.restart().asSeconds();
        bool invulnerable = true;

      //  if((float) elapsed.asSeconds() == 2.0f)
            invulnerable - false;
            hurt = false;
	}
	this->bbox = sprite.getGlobalBounds();
	if(this->health <= 0)
		is_dead = true;
		*/


}

void Player::set_weapon(int id)
{

	switch(id)
	{
		case Weapon::WeaponEnum::PISTOL:{
			this->weapon.init("Pistol", 999, 1);
		}break;
		case Weapon::WeaponEnum::SHOTGUN:{
			this->weapon.init("Shotgun", 999, 5);
		}break;
		default:{
			std::cerr << "[Player]: Error setting weapon!\n";
		}break;
	}
}
