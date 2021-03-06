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
#include "../entities/basicenemy.h"
#include "../entities/pickup.h"
#include "../weapon.h"
#include "../sound.hpp"
#include "../screen/hud.h"
#include "../levels/spawnpointlist.h"
#include "../levels/spawnpoint.h"
#include "gameoverstate.h"
#include "introstate.h"
#include <sstream>

class GameState : public State
{
private:
	Level level;
	Player player;
	std::vector<Mob*> mobs;
	std::vector<Bullet*> bullets;
	std::vector<Pickup*> pickups;

	//- States
	bool is_paused = false;
	bool has_sfx;
	bool clicked = false;

	//- Timing stuff
	sf::Clock item_cl;
	sf::Clock spawn_timer;

	//- Networking stuff (experimental)
	sf::UdpSocket socket;
	sf::IpAddress ip_address;
	unsigned short port;

	//- Audio stuff
	sf::Music music;
	Sound hit_snd, hurt_snd, pickup_snd, shoot_snd;

	//- UI stuff
	Hud hud;
	sf::Font font;

	//- Enemies stuff
	SpawnPointList splist;
	int wave;
	int enemies_left;
	int left_to_spawn;
	float enemy_speed = 100.0f;

	std::string level_name;

	void rotate(Player*, Game*, sf::Time);
	void rotate2(Mob*, Game*, sf::Time, sf::Vector2i);
	void spawn_enemies(int, SpawnPointList&);
	void player_shoot();
	void generate_pickup(int, int);
	bool check_mob_collision(float, float, int);
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

 	template<typename T>
 	void clear_vector(std::vector<T*>& v)
 	{
 		for(int i = 0; i < v.size(); ++i)
 			delete (v[i]);
 		v.clear();
 	}
};

#endif // GAMESTATE_H
