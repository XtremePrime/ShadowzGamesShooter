#include "stagestate.h"

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <SFML/Window.hpp>

#include "gamestate.h"
#include "introstate.h"

#define DEVTEST 0
#define DEMONS 1

StageState* StageState::_instance;

StageState* StageState::instance(){
	if(_instance == NULL)
		_instance = new StageState();
	return _instance;
}

void StageState::init(Game* game)
{
	font.loadFromFile("res/fonts/PressStart2P.ttf");

	//- Init select_box
	select_box.setSize(sf::Vector2f(mapsize+5, mapsize+5));
	select_box.setPosition(0, 0);
	select_box.setFillColor(sf::Color::Transparent);
	select_box.setOutlineColor(sf::Color::Red);
	select_box.setOutlineThickness(2.0f);

	//- Init levels
	levels[DEVTEST].init("devtest", 10, 10, mapsize, font, "Dev Test Level");
	levels[DEMONS].init("demons", game->get_gameobject()->width-mapsize-10, game->get_gameobject()->height-mapsize-10, mapsize, font, "Hell Level");

	//- Set text positions
	// levels[DEVTEST].text->setPosition(sf::Vector2f(10, 10+mapsize+15));
	// levels[DEMONS].text.setPosition(sf::Vector2f(-999, -999));

	//- Init texts
	auto init_text = [this](sf::Text& t, sf::Font f, std::string title, sf::Vector2f vec) -> void
	{
		t.setCharacterSize(15);
		t.setFont(f);
		t.setColor(sf::Color::White);
		t.setString(title);
		t.setPosition(vec);
	};

	init_text(level_names[DEVTEST], font, "DevTest Level", sf::Vector2f(400, 400));
}

void StageState::send_to_level(Game* game)
{
	switch(level_select)
	{
		case DEVTEST:
			game->get_gameobject()->level_name = "devtest";
			std::cout << "[StageState]: Loaded devtest\n";
		break;
		case DEMONS:
			game->get_gameobject()->level_name = "demons";
			std::cout << "[StageState]: Loaded demons\n";
		break;
		default:
			std::cerr << "[StageState]: Failed to load!\n";
		break;
	}
}

void StageState::move_selected(int v)
{
	std::cout << "[StageSelect]: Old level: " << level_select;

	if(level_select == 0 && v == -1) return;
	else if(level_select == TOTAL_LEVELS-1 && v == 1) return;

	level_select += v;

	std::cout << " / New level: " << level_select << "\n";
}

void StageState::handle_events(Game* game, sf::Event event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		switch(event.key.code)
		{
			case sf::Keyboard::Left:
			case sf::Keyboard::A:
			{
				move_selected(-1);
			}break;
			case sf::Keyboard::Right:
			case sf::Keyboard::D:
			{
				move_selected(1);
			}break;
			case sf::Keyboard::Return:
			{
				send_to_level(game);
				game->change_state(GameState::instance());
			}
			break;
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
	select_box.setPosition(levels[level_select].x-1, levels[level_select].y-1);
}

void StageState::render(Game* game)
{
	for(int i = 0; i < TOTAL_LEVELS; ++i){
		game->get_window()->draw(levels[i].sprite);
	}

	game->get_window()->draw(select_box);
	game->get_window()->draw(level_names[DEVTEST]);
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
