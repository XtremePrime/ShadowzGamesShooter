#include "hud.h"

Hud::Hud(sf::Font f, int w, int h)
{
	init(f, w, h);
}

void Hud::init(sf::Font f, int w, int h)
{
	txr.loadFromFile("res/levels/hud.png");
	sprite.setTexture(txr);
	this->font = f;
	this->screen_height = h;
	this->screen_width = w;

	sprite.scale(SCALE, SCALE);
}

void Hud::update(sf::Time deltaTime, Player& player, Level& level)
{
	#define t(xr,yr) 5+(xr)-(yr/2)
	sprite.setPosition(t(player.get_x(), level.get_view().getSize().x), t((player.get_y()+screen_height)-HEIGHT*SCALE, level.get_view().getSize().y));
	#undef t
}

void Hud::render(sf::RenderWindow* win)
{
	win->draw(sprite);
}
