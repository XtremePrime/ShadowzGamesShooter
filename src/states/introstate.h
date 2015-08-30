#ifndef INTROSTATE_H
#define INTROSTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include "state.h"

class IntroState : public State
{
private:
	sf::Font font;
	sf::Text credits;
	sf::Text version;

	//- Notification stuff
	sf::FloatRect notification_text_box;
	sf::Text notification_text;
	sf::Clock n_timer;
	bool show_notification = false;

	sf::RectangleShape selector;
	sf::RectangleShape blackbox;
	sf::Texture ts_txr;
	sf::Sprite title_screen;
	int selected_id = 0;
	std::vector<sf::Text*> menu_options;
	const int MAX_OPTIONS = 5;
	sf::VideoMode desktop;

	int GAME_WIDTH = 860, GAME_HEIGHT = 640, MENU_OFFSET_Y = 90, MENU_OFFSET_X = 50; 

	//- Audio stuff
	sf::Music music;

	void move_selected(bool);
	void win_init();
protected:
	static IntroState* _instance;
	IntroState(){}
public:
	static IntroState* instance();
    ~IntroState(){}
	void init(Game* game);
	void cleanup();

	void handle_events(Game* game, sf::Event event);
	void update(Game* game, sf::Time deltaTime);
	void render(Game* game);

 	void pause();
 	void resume();
};

#endif // INTROSTATE_H
