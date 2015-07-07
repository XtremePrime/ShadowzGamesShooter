#include <SFML/Graphics.hpp>

#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
protected:
    std::string name;
    int x, y, w, h;
    bool removed;

    sf::Texture texture;
    sf::Sprite sprite;
    sf::FloatRect bbox;
public:
    virtual void init(int x, int y, int w, int h) = 0;
	virtual void render(sf::RenderWindow *win) = 0;
	virtual void update(sf::Time deltaTime) = 0;
	virtual void handle_events(sf::Event *event) = 0;

    bool intersects(Entity& e)
    {
        //- TODO collision with entity e
    }

    std::string get_name() { return this->name; }
    int get_x(){ return this->x; }
    int get_y(){ return this->y; }
    int get_w(){ return this->w; }
    int get_h(){ return this->h; }
    void set_x(int xx){ this->x = xx; }
    void set_y(int yy){ this->y = yy; }
    void remove(){ this->removed = true; }
};

#endif // ENTITY_H
