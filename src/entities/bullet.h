#ifndef BULLET_H
#define BULLET_H

#include <string>
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "../levels/tile.h"

class Bullet : public Entity
{
protected:
    int damage = 1;
	int speed = 200;
    int traveldist = 0;
    const int SIZE = 16;
    int vx = 0, vy = 0;
    void move(sf::Time);
public:
	Bullet(int, int, float, int);
	~Bullet(){}
	void init(int x, int y, int w, int h);
    void handle_events(sf::Event *event);
    void update(sf::Time deltaTime);
    void render(sf::RenderWindow *win);
    bool can_move(Tile* tile);

    // int get_hp() { return this->hp; }
    int get_dmg() { return this->damage; }
    int get_speed() { return this->speed; }
    // bool get_death() { return this->is_dead; }
};
#endif

