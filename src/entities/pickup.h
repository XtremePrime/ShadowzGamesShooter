#ifndef PICKUP_H
#define PICKUP_H

#include "entity.h"
#include <sstream>
#include <SFML/Graphics.hpp>

class Pickup : public Entity
{
private:
	int id;
	sf::Clock alive_timer;
public:
	Pickup(int, int, int, int ,int);
	~Pickup(){}
	void init(int x, int y, int w, int h){}
	void init(int id, int x, int y, int w, int h);
	void handle_events(sf::Event* ev){}
	void render(sf::RenderWindow*);
	void update(sf::Time);
	int get_id(){ return this->id; }

	sf::Clock& get_timer() { return this->alive_timer; }

	enum PickupCodes{
		HEALTH = 0,
		SHOTGUN = 1,
		SMG = 2
	};

};

#endif // PICKUP_H