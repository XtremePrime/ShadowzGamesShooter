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
	sf::RectangleShape selector;
	int selected_id;
	std::vector<sf::Text*> menu_options;
	const int MAX_OPTIONS = 4;

	void move_selected(bool);
protected:
	static IntroState* _instance;
	IntroState(){}
public:
	static IntroState* instance();
    ~IntroState(){}
	void init();
	void cleanup();

	void handle_events(Game* game, sf::Event event);
	void update(Game* game, sf::Time deltaTime);
	void render(Game* game);

 	void pause();
 	void resume();
};

#endif // INTROSTATE_H
