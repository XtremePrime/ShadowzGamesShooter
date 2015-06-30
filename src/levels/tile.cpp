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
	this->texture.loadFromFile(filepath);
	this->sprite.setTexture(texture);
	this->sprite.setPosition(x*SIZE, y*SIZE);
}

void Tile::update(sf::Time deltaTime)
{

}

void Tile::render(sf::RenderWindow *win)
{
	win->draw(this->sprite);
}
