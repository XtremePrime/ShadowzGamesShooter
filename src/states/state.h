#ifndef STATE_H
#define STATE_H

#include "../game.h"

class State
{
private:
public:
	virtual void init(Game* game) = 0;
	virtual void cleanup() = 0;

	virtual void handle_events(Game* game, sf::Event event) = 0;
	virtual void update(Game* game, sf::Time deltaTime) = 0;
	virtual void render(Game* game) = 0;

 	virtual void pause() = 0;
 	virtual void resume() = 0;

	void change_state(Game* game, State* state){
		game->change_state(state);
	}
	virtual ~State(){};
};

#endif // STATE_H
