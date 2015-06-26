#ifndef OPTIONSSTATE_H
#define OPTIONSSTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include "state.h"

class OptionsState : public State
{
private:
protected:
	static OptionsState* _instance;
	OptionsState(){}
public:
	static OptionsState* instance();
    ~OptionsState(){}
	void init();
	void cleanup();

	void handle_events(Game* game, sf::Event event);
	void update(Game* game, sf::Time deltaTime);
	void render(Game* game);

 	void pause();
 	void resume();
};

#endif // OPTIONSSTATE_H
