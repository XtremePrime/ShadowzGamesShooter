#ifndef BULLET_H
#define BULLET_H

#include <string>
#include <SFML/Graphics.hpp>
#include "entity.h"

class Bullet : public Entity
{
protected:
	int speed = 200;
	sf::RectangleShape rect;
    const int SIZE = 16;
    int vx = 0, vy = 0;
    void move(sf::Time);
public:
	Bullet(int, int, float);
	~Bullet();
	void init(int x, int y, int w, int h);
    void handle_events(sf::Event *event);
    void update(sf::Time deltaTime);
    void render(sf::RenderWindow *win);

    // int get_hp() { return this->hp; }
    // int get_dmg() { return this->dmg; }
    // bool get_death() { return this->is_dead; }
};
#endif
