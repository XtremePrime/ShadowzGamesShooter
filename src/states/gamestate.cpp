#include "gamestate.h"

#include <sstream>

GameState* GameState::_instance;

GameState* GameState::instance(){
	if(_instance == NULL)
		_instance = new GameState();
	return _instance;
}

void GameState::init()
{

}

void GameState::handle_events(Game* game, sf::Event event)
{

}

void GameState::update(Game* game,  sf::Time deltaTime)
{

}

void GameState::render(Game* game)
{

}

void GameState::cleanup()
{

}

void GameState::pause()
{

}

void GameState::resume()
{

}