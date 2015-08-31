#ifndef MOB_H
#define MOB_H

#include <string>
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "../levels/tile.h"

class Mob : public Entity
{
protected:
	int speed = 200, health;
    int points = 100;
    int vx, vy;
    int damage=1;

	sf::RectangleShape rect;
public:
    Mob();
	Mob(int, int, int, int);
	~Mob();
	void init(int x, int y, int w, int h);
    void handle_events(sf::Event *event);
    void update(sf::Time deltaTime);
    void render(sf::RenderWindow *win);
    void move2(int, int, sf::Time, int);
    void move(sf::Time);
    bool can_move(Tile* tile);

//    bool hasCollision(Tile* tile);

    int get_points(){return this->points;}
    int get_hp() { return this->health; }
    int get_dmg() { return this->damage; }
    void hurt(int dmg){this->health -= dmg;}
    int get_vx() { return this->vx; }
    int get_vy() { return this->vy; }
    // int get_dmg() { return this->dmg; }
    // bool get_death() { return this->is_dead; }
};
#endif

