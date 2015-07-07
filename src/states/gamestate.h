#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <cstdlib>
#include "state.h"
#include "../levels/level.h"
#include "../entities/player.h"
#include "../entities/entity.h"
#include "../entities/mob.h"


class GameState : public State
{
private:
	Level level;
	Player player;
	Mob mob;

	sf::IpAddress ip_address;
	unsigned short port;

	//- Networking stuff (experimental)
	sf::UdpSocket socket;
protected:
	static GameState* _instance;
	GameState(){}
public:
	static GameState* instance();
    ~GameState(){}
	void init(Game* game);
	void cleanup();

	void handle_events(Game* game, sf::Event event);
	void update(Game* game, sf::Time deltaTime);
	void render(Game* game);

 	void pause();
 	void resume();
};

#endif // GAMESTATE_H
