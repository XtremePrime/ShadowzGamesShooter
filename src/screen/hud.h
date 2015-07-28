#ifndef HUD_H
#define HUD_H

#include "../levels/level.h"
#include "../entities/player.h"
#include <SFML/Graphics.hpp>

class Hud
{
private:
	sf::Texture txr;
	sf::Sprite sprite;
	sf::Font font;
public:
	Hud();
	~Hud(){}

	void init(sf::Font);
	
	void update(sf::Time, Player&, Level&);
	void render(sf::RenderWindow*);
};

#endif // HUD_H