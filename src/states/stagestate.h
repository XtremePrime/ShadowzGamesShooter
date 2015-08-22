#ifndef STAGESTATE_H
#define STAGESTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "state.h"

class StageState : public State
{
private:
	int mapsize = 250;

	struct StageMap{
		std::string name;
		int x, y;
		sf::Texture txr;
		sf::Sprite sprite;
		sf::Text* text;

		void init(std::string n, int xx, int yy, int s, sf::Font f, std::string title)
		{
			name = n;
			x = xx;
			y = yy;
			std::string path = "res/levels/"+name+"/map.png";
			std::cout << path << "\n";
			txr.loadFromFile(path);
			sprite.setTexture(txr);
			sprite.setPosition(sf::Vector2f(x, y));
			sprite.setScale(s/sprite.getLocalBounds().width, s/sprite.getLocalBounds().height);

			// text->setCharacterSize(15);
			// text->setFont(f);
			// text->setColor(sf::Color::White);
			// text->setString(title);
			// text->setPosition(sf::Vector2f(0, 0));
		}
	};

	sf::Font font;
	int level_select = 0;
	sf::RectangleShape select_box;

	#define t 2
	const int TOTAL_LEVELS = t;
	StageMap levels[t];
	sf::Text level_names[t];
	#undef t

	sf::SoundBuffer shoot_buf; sf::Sound shoot_snd;

	void send_to_level(Game*);
	void move_selected(int);
protected:
	static StageState* _instance;
	StageState(){}
public:
	static StageState* instance();
    ~StageState(){}
	void init(Game* game);
	void cleanup();

	void handle_events(Game* game, sf::Event event);
	void update(Game* game, sf::Time deltaTime);
	void render(Game* game);

 	void pause();
 	void resume();
};

#endif // STAGESTATE_H
