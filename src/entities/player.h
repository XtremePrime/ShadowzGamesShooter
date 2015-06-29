#ifndef PLAYER_H
#define PLAYER_H

class Player : public Mob
{
	void handle_events(sf::Event*);
	void render(sf::RenderWindow*);
	void update(sf::Time);
};

#endif // PLAYER_H