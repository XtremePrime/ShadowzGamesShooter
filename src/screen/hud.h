#ifndef HUD_H
#define HUD_H

#include "../levels/level.h"
#include "../entities/player.h"
#include <SFML/Graphics.hpp>
#include <sstream>

class Hud
{
private:
	int screen_width, screen_height;

	sf::Font font;

	struct ShadowedText{
		sf::Text text;
		sf::Text shadow;

		void init(sf::Font& f, std::string title, sf::Vector2f coord)
		{
			text.setCharacterSize(15);
			text.setFont(f);
			text.setColor(sf::Color::White);
			text.setString(title);
			text.setPosition(coord);

			shadow.setCharacterSize(15);
			shadow.setFont(f);
			shadow.setColor(sf::Color::Black);
			shadow.setString(title);
			shadow.setPosition(sf::Vector2f(coord.x+1, coord.y-1));
		}

		void setPosition(int x, int y){
			text.setPosition(x, y);
			shadow.setPosition(x+1, y-1);
		}

		void render(sf::RenderWindow* win){
			win->draw(shadow);
			win->draw(text);
		}

		void setString(std::string str){
			text.setString(str);
			shadow.setString(str);
		}
	};

	ShadowedText wave, score, enemies_left;

	//- Health bar
	sf::Texture hpbar_txr; sf::Sprite hpbar;
public:
	Hud(sf::Font, int, int);
	Hud(){}
	~Hud(){}

	void init(sf::Font, int, int);

	void update(sf::Time, Player&, Level&, int, int);
	void render(sf::RenderWindow*);
};

#endif // HUD_H
