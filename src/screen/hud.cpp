#include "hud.h"

Hud::Hud()
{
	// init()
}

void Hud::init(sf::Font f)
{
	txr.loadFromFile("res/levels/hud.png");
	sprite.setTexture(txr);
	this->font = f;
}

void Hud::update(sf::Time deltaTime, Player& player, Level& level)
{
	#define t(xr,yr) 5+xr-(yr/2)
	sprite.setPosition(t(player.get_x(), level.get_view().getSize().x), t(player.get_y(), level.get_view().getSize().y));
	#undef t
}

void Hud::render(sf::RenderWindow* win)
{
	win->draw(sprite);
}