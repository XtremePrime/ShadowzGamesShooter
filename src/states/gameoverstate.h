#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "state.h"
#include "gamestate.h"
#include "introstate.h"

class GameOverState : public State
{
private:
	sf::Font font;

	int GAME_WIDTH, GAME_HEIGHT, MENU_OFFSET_Y = 90, MENU_OFFSET_X = 50;
	sf::RectangleShape selector;
	sf::Texture ts_txr;
	sf::Sprite title_screen;
	int selected_id = 0;
	std::vector<sf::Text*> menu_options;
	const int MAX_OPTIONS = 2;

	//- Audio stuff
	sf::Music music;
	sf::Clock music_delay;

	sf::Text review;

	void move_selected(bool);
	void win_init();
protected:
	static GameOverState* _instance;
	GameOverState(){}
public:
	static GameOverState* instance();
    ~GameOverState(){}
	void init(Game* game);
	void cleanup();

	void handle_events(Game* game, sf::Event event);
	void update(Game* game, sf::Time deltaTime);
	void render(Game* game);

 	void pause();
 	void resume();
};

#endif // GAMEOVERSTATE_H
