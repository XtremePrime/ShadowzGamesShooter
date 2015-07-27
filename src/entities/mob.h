#ifndef MOB_H
#define MOB_H

#include <string>
#include <SFML/Graphics.hpp>
#include "entity.h"


class Mob : public Entity
{
protected:
	int speed = 200, health;
    int points = 100;

	sf::RectangleShape rect;


public:
    Mob();
	Mob(int, int, int, int);
	~Mob();
	void init(int x, int y, int w, int h);
    void handle_events(sf::Event *event);
    void update(sf::Time deltaTime);
    void render(sf::RenderWindow *win);
    void move2(int xp, int yp);
    int dmg=10;
//    bool hasCollision(Tile* tile);

    int get_points(){return this->points;};
    int get_hp() { return this->health; };
    void damage(int dmg){this->health -= dmg;};
    // int get_dmg() { return this->dmg; }
    // bool get_death() { return this->is_dead; }
};
#endif

