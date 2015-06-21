#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

class State;
class Game
{
private:
	sf::RenderWindow window;
	const int GAME_WIDTH = 860, GAME_HEIGHT = 640;
	bool is_running = true;
	sf::Clock clock;
	std::vector<State*> state_stack;
	sf::Image icon;

	void init();
	void update(sf::Time);
	void handle_events(sf::Event);
	void render(sf::RenderWindow&);
public:
	void change_state(State* state);
	void push_state(State* state);
	void pop_state();

	void run();
	void quit(){
		this->is_running = false;
		this->window.close();
	}

	sf::RenderWindow* get_window() { return &window; }
};
#endif // GAME_H
