#ifndef LEVEL_H
#define LEVEL_H

class Level
{
private:
public:
	void init();
	void handle_events(sf::Event&);
	void render(sf::Time);
	void update(sf::RenderWindow&);
};

#endif // LEVEL_H