#include "game.h"
#include "states/state.h"
#include "states/gamestate.h"

void Game::init()
{
	//- Init Win Window
	this->window.create(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), "Untitled Game", sf::Style::Titlebar | sf::Style::Close);
	this->window.setVerticalSyncEnabled(true);
	this->window.setKeyRepeatEnabled(false);

	//- Handle RNG
	srand(time(NULL));

	//- Load favicon
	#define FAVICON_SIZE 32
	// icon.loadFromFile("");
	// window.setIcon(FAVICON_SIZE,FAVICON_SIZE,icon.getPixelsPtr());
	#undef FAVICON_SIZE
}

void Game::handle_events(sf::Event ev)
{
	while(window.pollEvent(ev))
	{
		//- Handle state events first, then general states.
		state_stack.back()->handle_events(this, ev);
		switch(ev.type)
		{
			case sf::Event::Closed:
			{
				window.close();
				quit();
			}break;
			case sf::Event::KeyPressed:
			{
				if(ev.key.code == sf::Keyboard::Escape)
				{
					window.close();
					quit();
				}
			}break;
		}
	}
}

void Game::update(sf::Time dt)
{
	//- Update current state
	state_stack.back()->update(this, dt);
}

void Game::render(sf::RenderWindow &window)
{
	window.clear();
	state_stack.back()->render(this);
	window.display();
}

void Game::change_state(State* state)
{
	//- Cleanup current state
	if(!state_stack.empty()){
		state_stack.back()->cleanup();
		state_stack.pop_back();
	}

	//- Store & Init new state
	state_stack.push_back(state);
	state_stack.back()->init();
}

void Game::push_state(State* state)
{
	//- Pause current state
	if(!state_stack.empty()){
		state_stack.back()->pause();
	}

	//- Store & Init new state
	state_stack.push_back(state);
	state_stack.back()->init();
}

void Game::pop_state()
{
	//- Cleanup current state
	if(!state_stack.empty()){
		state_stack.back()->cleanup();
		state_stack.pop_back();
	}

	//- Resume previous state
	if(!state_stack.empty()){
		state_stack.back()->resume();
	}
}

void Game::run()
{
	init();
	push_state(GameState::instance());
	while(is_running)
	{
		sf::Event event;
		handle_events(event);
		update(clock.restart());
		render(window);
	}
}
