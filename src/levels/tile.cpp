#include "tile.h"
#include <iostream>

Tile::Tile(int xx, int yy, std::string filepath)
{
	init(xx, yy, filepath);
}

void Tile::init(int xx, int yy, std::string filepath)
{
	this->x = xx;
	this->y = yy;
	std::cout << this->x << "/" << this->y << "\n";
	this->texture.loadFromFile(filepath);
	this->sprite.setTexture(texture);
}

void Tile::update(sf::Time deltaTime)
{
	this->sprite.setPosition(x*SIZE, y*SIZE);
}

void Tile::render(sf::RenderWindow *win)
{
	win->draw(this->sprite);
}
