#include "optionsstate.h"

#include "gamestate.h"
#include "introstate.h"

#include <sstream>

OptionsState* OptionsState::_instance;

OptionsState* OptionsState::instance(){
	if(_instance == NULL)
		_instance = new OptionsState();
	return _instance;
}

void OptionsState::init(Game* game)
{

}

void OptionsState::handle_events(Game* game, sf::Event event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		switch(event.key.code)
		{
			case sf::Keyboard::Escape:
			{
				game->change_state(IntroState::instance());
			}break;
			default:
			break;
		}
	}
}

void OptionsState::update(Game* game,  sf::Time deltaTime)
{

}

void OptionsState::render(Game* game)
{

}

void OptionsState::cleanup()
{
	_instance = NULL;
}

void OptionsState::pause()
{

}

void OptionsState::resume()
{

}