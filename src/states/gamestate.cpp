#include "gamestate.h"
#include "introstate.h"


#include <sstream>

GameState* GameState::_instance;

GameState* GameState::instance(){
	if(_instance == NULL)
		_instance = new GameState();
	return _instance;
}

void GameState::init(Game* game)
{
	this->ip_address = game->get_gameobject()->ip_address;
	this->port = game->get_gameobject()->port;

	//- Binding to the port to establish connection
	if (socket.bind(port) != sf::Socket::Done)
		std::cout << "Could not connect to: " << "localhost" << "!\n";

	// char data[] = "abc";
	// if (socket.send(data, 3, game->get_gameobject()->ip_address, game->get_gameobject()->port) != sf::Socket::Done)
	// {
   		// std::cout << "Sent bby\n";
	// }

	level.init("res/levels/devtest/");
	player.init(100, 100, 16, 32);
	mob.init(60, 60, 30, 30);
}

void GameState::handle_events(Game* game, sf::Event event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		switch(event.key.code)
		{
			case sf::Keyboard::Escape:
			{
				//@TODO: Open menu
				// game->change_state(IntroState::instance());
				// game->get_state_stack().back()->init();

				game->quit();
			}break;
			default:
			break;
		}
	}
	//- handle EVERYTHING
	level.handle_events(&event);
	mob.handle_events(&event);
	player.handle_events(&event);
}

void GameState::update(Game* game,  sf::Time deltaTime)
{
	//- update EVERYTHING
	level.update(deltaTime);
	mob.update(deltaTime);
	player.update(deltaTime);

	//- Player rotation (Experimental)
	sf::Vector2f curPos;
	//Get player global bounds and mouse pos according to window(with conv)
	curPos.x = player.get_model().getGlobalBounds().left + (float)player.get_w()/2-1;
	curPos.y = player.get_model().getGlobalBounds().top + (float)player.get_h()/2-1;
	sf::Vector2i pos = sf::Mouse::getPosition(*game->get_window());
	pos = sf::Vector2i(game->get_window()->mapPixelToCoords(pos, level.get_view()));

	#define DEGREE (180 / 3.14159265)

	//DeltaX/Y is the position of the mouse - the current player position.
	//Rotation is arctangent of dy and dx multiplied by 180/PI
	float dx = pos.x - curPos.x;
	float dy = pos.y - curPos.y;
	float rotation = (atan2(dy, dx)) * DEGREE;

	// std::cout << dx << "/" << dy << "/" << rotation << "\n";
	player.get_model().setRotation(rotation+180);

	#undef ANGLE
}

void GameState::render(Game* game)
{
	//- render EVERYTHING
	level.render(game->get_window(), player.get_x(), player.get_y());
	mob.render(game->get_window());
	player.render(game->get_window());
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
