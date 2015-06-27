#include "gamestate.h"
#include "introstate.h"


#include <sstream>

GameState* GameState::_instance;

GameState* GameState::instance(){
	if(_instance == NULL)
		_instance = new GameState();
	return _instance;
}

void GameState::init()
{
	dev_level.init("res/levels/devtest/");
}

void GameState::handle_events(Game* game, sf::Event event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		switch(event.key.code)
		{
			case sf::Keyboard::Escape:
			{
				game->change_state(IntroState::instance());
				game->get_state_stack().back()->init();
			}break;
			default:
			break;
		}
	}
}

void GameState::update(Game* game,  sf::Time deltaTime)
{
	dev_level.update(deltaTime);
}

void GameState::render(Game* game)
{
	dev_level.render(game->get_window());
}

void GameState::cleanup()
{
	_instance = NULL;
}

void GameState::pause()
{

}

void GameState::resume()
{

}