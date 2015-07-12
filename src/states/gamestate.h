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
#include "../entities/bullet.h"

class GameState : public State
{
private:
	Level level;
	Player player;
	std::vector<Mob*> mobs;
	std::vector<Bullet*> bullets;

	bool is_paused = false;
	bool has_sfx;

	//- Networking stuff (experimental)
	sf::UdpSocket socket;
	sf::IpAddress ip_address;
	unsigned short port;

	//- Audio stuff
	sf::Music music;
	sf::SoundBuffer shoot_buf; sf::Sound shoot_snd;

	//- UI stuff
	sf::Font font;
	sf::Text score_txt;

	void rotate(Player*, Game*, sf::Time);
	void rotate2(Mob*, Game*, sf::Time, sf::Vector2i);
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
