#ifndef HUD_H
#define HUD_H

#include "../levels/level.h"
#include "../entities/player.h"
#include <SFML/Graphics.hpp>
#include <sstream>

class Hud
{
private:
	sf::Font font;

	//- Health bar
	sf::Texture hpbar_txr; sf::Sprite hpbar;

	sf::Text score_txt;

	int screen_width, screen_height;
public:
	Hud(sf::Font, int, int);
	Hud(){}
	~Hud(){}

	void init(sf::Font, int, int);

	void update(sf::Time, Player&, Level&);
	void render(sf::RenderWindow*);
};

#endif // HUD_H
