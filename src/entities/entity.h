#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
protected:
    std::string name;
    int x, y, w, h;

    sf::Texture texture;
    sf::Sprite sprite;
    sf::FloatRect bbox;
public:
    bool removed = false;

    virtual void init(int x, int y, int w, int h) = 0;
	virtual void render(sf::RenderWindow *win) = 0;
	virtual void update(sf::Time deltaTime) = 0;
	virtual void handle_events(sf::Event *event) = 0;

    bool intersects(Entity& e){
        return this->bbox.intersects(e.get_bbox());
    }

    std::string get_name() { return this->name; }
    int get_x(){ return this->x; }
    int get_y(){ return this->y; }
    int get_w(){ return this->w; }
    int get_h(){ return this->h; }
    void set_x(int xx){ this->x = xx; }
    void set_y(int yy){ this->y = yy; }
    void remove(){ this->removed = true; }
    float get_rotation(){ return this->sprite.getRotation(); }
    sf::Sprite& get_model() { return this->sprite; }
    sf::FloatRect& get_bbox() { return this->bbox; }

};

#endif // ENTITY_H
