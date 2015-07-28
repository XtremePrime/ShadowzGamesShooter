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

	const float SCALE = 2.f;
	const int WIDTH = 512;
	const int HEIGHT = 84;

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
