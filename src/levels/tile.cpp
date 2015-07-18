#include "tile.h"
#include <iostream>

// Tile::Tile(int xx, int yy, std::string filepath)
// {
// 	init(xx, yy, filepath);
// }

Tile::Tile(int xx, int yy, sf::Texture& tx)
{
	init(xx, yy, tx);
}

Tile::Tile(int xx, int yy, bool solid, sf::Texture& tx)
{
	this->is_collidable = solid;
	init(xx, yy, tx);
}

// void Tile::init(int xx, int yy, std::string filepath)
// {
// 	this->x = xx;
// 	this->y = yy;
// 	this->texture.loadFromFile(filepath);
// 	this->sprite.setTexture(texture);
// 	this->sprite.setPosition(x*SIZE, y*SIZE);
// }

void Tile::init(int xx, int yy, sf::Texture& tx)
{
	this->x = xx;
	this->y = yy;
	// this->texture.loadFromFile(filepath);
	this->sprite.setTexture(tx);
	this->sprite.setPosition(x*SIZE, y*SIZE);
	this->bbox = sprite.getGlobalBounds();
}

void Tile::update(sf::Time deltaTime)
{

}

void Tile::render(sf::RenderWindow *win)
{
	win->draw(this->sprite);
}
