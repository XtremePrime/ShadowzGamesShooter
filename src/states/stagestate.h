#ifndef STAGESTATE_H
#define STAGESTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include "state.h"

class StageState : public State
{
private:
	int level_select = 0;
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