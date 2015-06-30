#ifndef MOB_H
#define MOB_H

#include <string>
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "player.h"

class Mob : public Entity
{
private:

public:
    Mob(sf::Vector2f, Level, int);

    void init(sf::Vector2f, Level, int);

    Void move(sf::Vectorsf);
    bool hasCollision(Tile*);
    bool hitsPlayer(Tile*, Player);
    sf::Vector2f generate_Move(Level);

    void handle_events(sf::Event event);
    void update(sf::Time deltaTime);
    void render(sf::RenderWindow *win)

    int get_hp() { return this->hp; }
    int get_dmg() { return this->dmg; }
    bool get_death() { return this->is_dead; }
};
#endif

