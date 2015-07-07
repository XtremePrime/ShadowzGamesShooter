#include "stagestate.h"

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <SFML/Window.hpp>

#include "gamestate.h"
#include "introstate.h"

StageState* StageState::_instance;

StageState* StageState::instance(){
	if(_instance == NULL)
		_instance = new StageState();
	return _instance;
}

void StageState::init(Game* game)
{

}

void StageState::handle_events(Game* game, sf::Event event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		switch(event.key.code)
		{
			case sf::Keyboard::Return:
			{
				game->change_state(GameState::instance());
				std::cout << "GO!\n";
			}
			case sf::Keyboard::Escape:
			{
				game->change_state(IntroState::instance());
			}break;
			default:
            break;
		}
	}
}

void StageState::update(Game* game,  sf::Time deltaTime)
{

}

void StageState::render(Game* game)
{

}

void StageState::cleanup()
{
	_instance = NULL;
}

void StageState::pause()
{

}

void StageState::resume()
{

}
