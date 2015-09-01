#include "creditsstate.h"

CreditsState* CreditsState::_instance;

CreditsState* CreditsState::instance(){
	if(_instance == NULL)
		_instance = new CreditsState();
	return _instance;
}


void CreditsState::init(Game* game)
{
	//- Init screen
	texture.loadFromFile("res/screen/credits_screen.png");
	screen.setTexture(texture);
	screen.setPosition(0, 0);
}
void CreditsState::cleanup()
{

}

void CreditsState::handle_events(Game* game, sf::Event event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		switch(event.key.code)
		{
			case sf::Keyboard::Return:
			case sf::Keyboard::Escape:
			case sf::Keyboard::Space:
			{
				game->pop_state();
			}
			default:
			break;
		}
	}
}
void CreditsState::update(Game* game, sf::Time deltaTime)
{

}
void CreditsState::render(Game* game)
{
	game->get_window()->draw(screen);
}

void CreditsState::pause()
{

}
void CreditsState::resume()
{

}