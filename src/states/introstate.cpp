#include "introstate.h"

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <SFML/Window.hpp>

#include "stagestate.h"
#include "gamestate.h"

IntroState* IntroState::_instance;

IntroState* IntroState::instance(){
	if(_instance == NULL)
		_instance = new IntroState();
	return _instance;
}

void IntroState::init()
{
	desktop = sf::VideoMode::getDesktopMode();

	//- Load font
	font.loadFromFile("res/fonts/PressStart2P.ttf");

	//- Push menu options
	for(int i = 0; i < MAX_OPTIONS; ++i)
		menu_options.push_back(new sf::Text());

	//- Init menu options
	for(int i = 0; i < menu_options.size(); ++i)
	{
		menu_options[i]->setCharacterSize(15);
		menu_options[i]->setFont(font);
		menu_options[i]->setColor(sf::Color::White);
	}
	menu_options[0]->setString("START GAME (SINGLEPLAYER)");
	menu_options[1]->setString("START GAME (MULTIPLAYER)");
	menu_options[2]->setString("OPTIONS (FULLSCREEN/WINDOWED)");
	menu_options[3]->setString("EXIT");

	//- Init selector
	selector.setSize(sf::Vector2f(14, 14));
	selector.setFillColor(sf::Color::White);


	//- Init credit text
	credits.setCharacterSize(15);
	credits.setFont(font);
	credits.setColor(sf::Color::White);
	credits.setString("© 2015 ShadowzGames");

	win_init();

	std::cout << desktop.width << "/" << desktop.height << "\n";
}

void IntroState::win_init()
{
	for(int i = 0; i < MAX_OPTIONS; ++i)
		menu_options[i]->setPosition(GAME_WIDTH/2-90, (i*32)+(GAME_HEIGHT/2)+MENU_OFFSET_Y);
	selector.setPosition(GAME_WIDTH/2-114, (selected_id*32)+(GAME_HEIGHT/2)+MENU_OFFSET_Y);
	credits.setPosition(GAME_WIDTH-310, GAME_HEIGHT-30);
}

void IntroState::move_selected(bool up)
{
	if(!up)
	{
		if(selected_id >= MAX_OPTIONS-1)
			selected_id = 0;
		else
			selected_id++;
	}else{
		if(selected_id <= 0)
			selected_id = MAX_OPTIONS-1;
		else
			selected_id--;
	}

	selector.setPosition(GAME_WIDTH/2-114, (selected_id*32)+(GAME_HEIGHT/2)+MENU_OFFSET_Y);

}

void IntroState::handle_events(Game* game, sf::Event event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		switch(event.key.code)
		{
			case sf::Keyboard::Up:
			case sf::Keyboard::W:
			{
				move_selected(true);
			}break;
			case sf::Keyboard::Down:
			case sf::Keyboard::S:
			{
				move_selected(false);
			}break;
			case sf::Keyboard::Return:
			{
				switch(selected_id)
				{
					case 0: //- Singleplayer
						game->change_state(GameState::instance());
						game->get_state_stack().back()->init();
					break;
					case 1: //- Multiplayer

					break;
					case 2: //- Options
						if(!game->get_fullscreen())
						{
							GAME_WIDTH = desktop.width; GAME_HEIGHT = desktop.height;
							game->get_window()->create(desktop, "Untitled Game", sf::Style::Fullscreen);
							game->set_fullscreen(true);
						}else
						{
							GAME_WIDTH = 860; GAME_HEIGHT = 640;
							game->get_window()->create(sf::VideoMode(860,640), "Untitled Game", sf::Style::Titlebar | sf::Style::Close);
							game->set_fullscreen(false);
						}
						win_init();
					break;
					case 3: //- Exit
						game->quit();
					break;
				}
			}break;
			default:
			break;
		}
	}
}

void IntroState::update(Game* game,  sf::Time deltaTime)
{

}

void IntroState::render(Game* game)
{
	for(int i = 0; i < menu_options.size(); ++i)
		game->get_window()->draw(*menu_options[i]);
	game->get_window()->draw(selector);
	game->get_window()->draw(credits);
}

void IntroState::cleanup()
{
	_instance = NULL;
}

void IntroState::pause()
{

}

void IntroState::resume()
{

}
