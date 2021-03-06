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
	this->speed = 200;
	this->health = 14;

	//- Init sprite
	texture.loadFromFile("res/models/player_1.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, w, h));
	sprite.rotate(-90);
	// sprite.setSize(sf::Vector2f(w, h));
	sprite.setPosition(sf::Vector2f(x, y));
	this->bbox = sprite.getGlobalBounds();
	sprite.setOrigin(w/2, h/2);

	//- Init keys
	keys["up"] = sf::Keyboard::W;
	keys["down"] = sf::Keyboard::S;
	keys["left"] = sf::Keyboard::A;
	keys["right"] = sf::Keyboard::D;
	keys["arrow-up"] = sf::Keyboard::Up;
	keys["arrow-down"] = sf::Keyboard::Down;
	keys["arrow-left"] = sf::Keyboard::Left;
	keys["arrow-right"] = sf::Keyboard::Right;


	inv_timer.restart();
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

void Player::move(sf::Time dt)
{
    vx = vy = 0;

    #define press(key) sf::Keyboard::isKeyPressed(key)
    if(!is_standard_movement)
    {
		if(press(keys["up"])){
			vx -= speed * cos(sprite.getRotation() * RADIAN);
    		vy -= speed * sin(sprite.getRotation() * RADIAN);
		}else if(press(keys["down"])){
			vx += speed * cos(sprite.getRotation()* RADIAN);
    		vy += speed * sin(sprite.getRotation()* RADIAN);
		}
		if(press(keys["right"])){
			vx += speed * sin(sprite.getRotation() * RADIAN);
			vy -= speed * cos(sprite.getRotation() * RADIAN);
		}else if(press(keys["left"])){
			vx -= speed * sin(sprite.getRotation()* RADIAN);
			vy += speed * cos(sprite.getRotation()* RADIAN);
		}
	}else{
		if(press(keys["up"]) || press(keys["arrow-up"])){
			vy -= speed;
			// vy -= 1;
		}else if(press(keys["down"]) || press(keys["arrow-down"])){
			vy += speed;
			// vy += 1;
		}
		if(press(keys["right"]) || press(keys["arrow-right"])){
			vx += speed;
			// vx += 1;
		}else if(press(keys["left"]) || press(keys["arrow-left"])){
			vx -= speed;
			// vx -= 1;
		}
	}
	#undef t
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

void Player::move2(int xa, int ya, sf::Time dt, int state)
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
	sprite.setPosition(sf::Vector2f(x, y));
}

void Player::update(sf::Time deltaTime)
{
	move(deltaTime);
	if(this->health <= 0)
		is_dead = true;

	if(this->weapon.get_ammo() <= 0)
		set_weapon(Weapon::WeaponEnum::PISTOL);

	this->bbox = sprite.getGlobalBounds();
}

void Player::set_weapon(int id)
{
	switch(id)
	{
		case Weapon::WeaponEnum::PISTOL:{
			this->weapon.init("Pistol", 999, 0.75f, 1);
			this->weapon.set_id(Weapon::WeaponEnum::PISTOL);
		}break;
		case Weapon::WeaponEnum::SHOTGUN:{
			this->weapon.init("Shotgun", 90, 1.3f, 3);
			this->weapon.set_id(Weapon::WeaponEnum::SHOTGUN);
		}break;
		case Weapon::WeaponEnum::SMG:{
			this->weapon.init("Sub Machinegun", 240, 0.15f, 1);
			this->weapon.set_id(Weapon::WeaponEnum::PISTOL);
		}break;
		default:{
			std::cerr << "[Player]: Error setting weapon!\n";
		}break;
	}
}

void Player::get_pickup(int id)
{
	switch(id)
	{
		case Pickup::PickupCodes::HEALTH:
		{
			heal(2);
			if(this->health > 14)
				this->health = 14;
		}break;
		case Pickup::PickupCodes::SHOTGUN:
		{
			if(this->weapon.get_id() == Weapon::WeaponEnum::SHOTGUN)
				this->weapon.add_ammo(30);
			else
				set_weapon(Weapon::WeaponEnum::SHOTGUN);
		}break;
		case Pickup::PickupCodes::SMG:
		{
			if(this->weapon.get_id() == Weapon::WeaponEnum::SMG)
				this->weapon.add_ammo(60);
			else
				set_weapon(Weapon::WeaponEnum::SMG);
		}break;
		default:
			std::cerr << "[Player]: Error getting pickup!\n";
		break;
	}
}
