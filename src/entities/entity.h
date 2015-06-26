#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
private:
public:
	void init(int x, int y, int w, int h);

	virtual void render(sf::RenderWindow&) = 0;
	virtual void update(sf::Time) = 0;
	virtual void handle_events(sf::Event&) = 0;
};

#endif // ENTITY_H