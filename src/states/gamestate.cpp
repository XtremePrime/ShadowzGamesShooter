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
	player.init(game->get_gameobject(), 100, 100, 16, 32);
	mob.init(150, 150, 16, 32);
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
	}else if(event.type == sf::Event::MouseButtonPressed){
		if(event.mouseButton.button == sf::Mouse::Left)
		{
    		bullets.push_back(new Bullet(player.get_x(), player.get_y(), player.get_rotation()));
		}
	}else if(event.type == sf::Event::LostFocus){
		pause();
	}else if(event.type == sf::Event::GainedFocus){
		resume();
	}
	//- handle EVERYTHING
	level.handle_events(&event);
	if(!is_paused)
	{
		mob.handle_events(&event);
		player.handle_events(&event);
	}	
}

void GameState::update(Game* game,  sf::Time deltaTime)
{
	//- update EVERYTHING
	if(is_paused){return;}
	level.update(deltaTime);
	mob.update(deltaTime);
	player.update(deltaTime);
	for(Bullet* bullet : bullets){
		bullet->update(deltaTime);
	}

	//- Player rotation based on mouse loc
	rotate(&player, game, deltaTime);

	//- Rotate mobs towards player loc.$
	//@TODO: Still broken for mob, I don't care, let Razvan do it.
	rotate2(&mob, game, deltaTime, sf::Vector2i(player.get_x(), player.get_y()));

	//- Collision test!
	if(player.intersects(mob))
		std::cout << "Collision!\n";
}

//- Player specific rotate
void GameState::rotate(Player* p, Game* game, sf::Time deltaTime)
{
	//Get player global bounds and mouse pos according to window(with conv)
	sf::Vector2f curPos;
	curPos.x = p->get_model().getGlobalBounds().left + (float)p->get_w()/2-1;
	curPos.y = p->get_model().getGlobalBounds().top + (float)p->get_h()/2-1;
	sf::Vector2i pos = sf::Mouse::getPosition(*game->get_window());
	pos = sf::Vector2i(game->get_window()->mapPixelToCoords(pos, level.get_view()));

	#define DEGREE (180 / 3.14159265)

	//DeltaX/Y is the position of the mousetostage - the current player position.
	//Rotation is arctangent of dy and dx multiplied by 180/PI
	float dx = pos.x - curPos.x;
	float dy = pos.y - curPos.y;
	float rotation = (atan2(dy, dx)) * DEGREE;

	p->get_model().setRotation(rotation+180);

	#undef DEGREE
}

//- Mob specific rotate
void GameState::rotate2(Mob* mob, Game* game, sf::Time deltaTime, sf::Vector2i pos)
{
	sf::Vector2f curPos;
	curPos.x = mob->get_model().getGlobalBounds().left + (float)mob->get_w()/2-1;
	curPos.y = mob->get_model().getGlobalBounds().top + (float)mob->get_h()/2-1;

	#define DEGREE (180 / 3.14159265)

	//DeltaX/Y is the position of the mousetostage - the current player position.
	//Rotation is arctangent of dy and dx multiplied by 180/PI
	float dx = pos.x - curPos.x;
	float dy = pos.y - curPos.y;
	float rotation = (atan2(dy, dx)) * DEGREE;

	mob->get_model().setRotation(rotation+180);

	#undef DEGREE
}

void GameState::render(Game* game)
{
	//- render EVERYTHING
	level.render(game->get_window(), player.get_x(), player.get_y());
	mob.render(game->get_window());
	player.render(game->get_window());
	for(Bullet* bullet : bullets){
		bullet->render(game->get_window());
	}
}

void GameState::cleanup()
{
	_instance = NULL;
}

void GameState::pause()
{
	is_paused = true;
}

void GameState::resume()
{
	is_paused = false;
}
