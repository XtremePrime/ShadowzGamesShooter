#ifndef MOB_H
#define MOB_H

#include <string>
#include <SFML/Graphics.hpp>
#include "entity.h"

class Mob : public Entity
{
protected:
	int speed = 200, hp;
	sf::RectangleShape rect;
public:
	Mob();
	~Mob();
	void init(int x, int y, int w, int h);
    void handle_events(sf::Event *event);
    void update(sf::Time deltaTime);
    void render(sf::RenderWindow *win);

    // int get_hp() { return this->hp; }
    // int get_dmg() { return this->dmg; }
    // bool get_death() { return this->is_dead; }
};
#endif

