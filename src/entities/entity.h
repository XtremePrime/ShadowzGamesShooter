#include <SFML/Graphics.hpp>

#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
private:
public:
	// void init(int x, int y, int w, int h);
	std::string name;
    int x, y, w, h;


    float get_x(){ return coord.x; }
    float get_y(){ return coord.y; }
    bool intersects(Entity e)
    void remove()
    bool remove;
    bool touched(Entity e){if }

	void render(sf::RenderWindow *win)
	virtual void update(sf::Time deltaTime) ;
	virtual void handle_events(sf::Event *event) = 0;
};

#endif // ENTITY_H
