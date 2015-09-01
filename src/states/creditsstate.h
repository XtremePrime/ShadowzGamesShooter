#ifndef CREDITSSTATE_H
#define CREDITSSTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include "state.h"

class CreditsState : public State
{
private:
	sf::Texture texture;
	sf::Sprite screen;
protected:
	static CreditsState* _instance;
	CreditsState(){}
public:
	static CreditsState* instance();
    ~CreditsState(){}
	void init(Game* game);
	void cleanup();

	void handle_events(Game* game, sf::Event event);
	void update(Game* game, sf::Time deltaTime);
	void render(Game* game);

 	void pause();
 	void resume();
};

#endif // CREDITSSTATE_H
