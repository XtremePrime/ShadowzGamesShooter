#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "gameobject.hpp"

class State;
class Game
{
private:
	sf::RenderWindow window;
	int game_width = 860, game_height = 640;
	bool is_running = true;
	GameObject gameobject;
	sf::Clock clock;
	std::vector<State*> state_stack;
	sf::Image icon;
	sf::Texture cursor_txr;
	sf::Sprite cursor;
	sf::ContextSettings settings;

	void init();
	void create_files(int);
	int has_files();
	void setup_gameobject();

	void update(sf::Time);
	void handle_events(sf::Event);
	void render(sf::RenderWindow&);

public:
	void change_state(State* state);
	void push_state(State* state);
	void pop_state();

	void run();
	void quit();

	sf::RenderWindow* get_window() { return &window; }
	GameObject* get_gameobject() { return &gameobject; }
	sf::Sprite* get_cursor() { return &cursor; }
	std::vector<State*> get_state_stack() { return state_stack; }
	int get_width() { return this->game_width; }
	int get_height() { return this->game_height; }
	// bool get_fullscreen() { return this->is_fullscreen; }
	// void set_fullscreen(bool state) { this->is_fullscreen = state; }
};
#endif // GAME_H
