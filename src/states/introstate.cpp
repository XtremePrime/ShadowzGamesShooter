#include "introstate.h"

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <SFML/Window.hpp>

#include "stagestate.h"
#include "gamestate.h"
#include "optionsstate.h"

IntroState* IntroState::_instance;

IntroState* IntroState::instance(){
	if(_instance == NULL)
		_instance = new IntroState();
	return _instance;
}

void IntroState::init(Game* game)
{
	GAME_WIDTH = game->get_gameobject()->width;
	GAME_HEIGHT = game->get_gameobject()->height;

	//- Load font
	font.loadFromFile("res/fonts/PressStart2P.ttf");

	//- Push menu options
	for(int i = 0; i < MAX_OPTIONS; ++i)
		menu_options.push_back(new sf::Text("", font, 15));

	//- Init menu options
	for(int i = 0; i < menu_options.size(); ++i)
		menu_options[i]->setColor(sf::Color::White);
		// menu_options[i]->setCharacterSize(15);
		// menu_options[i]->setFont(font);
		
	menu_options[0]->setString("START GAME (SINGLEPLAYER)");
	menu_options[1]->setString("HOST");
	menu_options[2]->setString("JOIN");
	menu_options[3]->setString("OPTIONS (FULLSCREEN/WINDOWED)");
	menu_options[4]->setString("EXIT");

	//- Init selector
	selector.setSize(sf::Vector2f(14, 14));
	selector.setFillColor(sf::Color::White);


	//- Init credit text
	credits.setCharacterSize(15);
	credits.setFont(font);
	credits.setColor(sf::Color::White);
	credits.setString("© 2015 ShadowzGames");

	version.setCharacterSize(15);
	version.setFont(font);
	version.setColor(sf::Color::White);
	version.setString(game->get_gameobject()->version);

	win_init();

	//- Sound & Music init
	music.openFromFile("res/music/mainmenu.flac");
	if(game->get_gameobject()->has_music)
		music.play();
}

void IntroState::win_init()
{
	for(int i = 0; i < MAX_OPTIONS; ++i)
		menu_options[i]->setPosition(GAME_WIDTH/2-90, (i*32)+(GAME_HEIGHT/2)+MENU_OFFSET_Y);
	selector.setPosition(GAME_WIDTH/2-114, (selected_id*32)+(GAME_HEIGHT/2)+MENU_OFFSET_Y);
	credits.setPosition(GAME_WIDTH-310, GAME_HEIGHT-30);
	version.setPosition(10, GAME_HEIGHT-30);
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
						game->get_gameobject()->is_multiplayer = false;
						game->get_gameobject()->port = 7777;
						game->get_gameobject()->ip_address = "127.0.0.1";
						game->change_state(GameState::instance());
						music.stop();
					break;
					case 1: //- Host
						game->get_gameobject()->is_multiplayer = true;
						game->change_state(GameState::instance());
					break;
					case 2: //- Join
					break;
					case 3: //- Options
						game->push_state(OptionsState::instance());

						// if(!game->get_fullscreen())
						// {
						// 	GAME_WIDTH = desktop.width; GAME_HEIGHT = desktop.height;
						// 	game->get_window()->create(desktop, "Untitled Game", sf::Style::Fullscreen);
						// 	game->set_fullscreen(true);
						// }else
						// {
						// 	GAME_WIDTH = 860; GAME_HEIGHT = 640;
						// 	game->get_window()->create(sf::VideoMode(860,640), "Untitled Game", sf::Style::Titlebar | sf::Style::Close);
						// 	game->set_fullscreen(false);
						// }
						// win_init();
					break;
					case 4: //- Exit
						game->quit();
					break;
					default:
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
	game->get_window()->draw(version);
}

void IntroState::cleanup()
{
	for(int i = 0; i < menu_options.size(); ++i)
		delete (menu_options[i]);
	menu_options.clear();
	_instance = NULL;
}

void IntroState::pause()
{

}

void IntroState::resume()
{

}
