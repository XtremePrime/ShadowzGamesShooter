#include "game.h"
#include "states/state.h"
#include "states/gamestate.h"
#include "states/introstate.h"

#include <fstream>
#include <direct.h>

void Game::init()
{
	//- Init GameObject stuff
	char* tmp = getenv("APPDATA");
	gameobject.appdata.assign(tmp);
	std::string str = gameobject.appdata+"\\ShadowzGames";
	mkdir(str.c_str());
	gameobject.appdata = gameobject.appdata+"\\ShadowzGames\\";

	create_files(has_files());
	setup_gameobject();

	//- Init Win Window
	this->window.create(sf::VideoMode(game_width, game_height), "Untitled Game "+gameobject.version, sf::Style::Titlebar | sf::Style::Close);
	this->window.setVerticalSyncEnabled(true);
	this->window.setKeyRepeatEnabled(false);

	//- Handle RNG
	srand(time(NULL));

	//- Load favicon
	#define FAVICON_SIZE 32
	// icon.loadFromFile("");
	// window.setIcon(FAVICON_SIZE,FAVICON_SIZE,icon.getPixelsPtr());
	#undef FAVICON_SIZE
}

void Game::setup_gameobject()
{
	pugi::xml_document doc;
	std::string path = gameobject.appdata+"settings.xml";
	doc.load_file(path.c_str());

	pugi::xml_node settings_node = doc.child("settings");
    //- Setup screen dimensions!
    if(!settings_node.child("SCREEN").attribute("fullscreen").as_bool()){
        gameobject.width = settings_node.child("DIMENSIONS-WINDOWED").attribute("width").as_int();
        gameobject.height = settings_node.child("DIMENSIONS-WINDOWED").attribute("height").as_int();
    }else{
        gameobject.width = settings_node.child("DIMENSIONS-FULLSCREEN").attribute("width").as_int();
        gameobject.height = settings_node.child("DIMENSIONS-FULLSCREEN").attribute("height").as_int();
    }

    //- Setup fullscreen status
    gameobject.is_standard_movement = settings_node.child("SCREEN").attribute("fullscreen").as_bool();

    //- Setup movement status
    gameobject.is_standard_movement = settings_node.child("CONTROLS").attribute("standard-movement").as_bool();

    //- Setup audio status
    gameobject.has_music = settings_node.child("AUDIO").attribute("music").as_bool();
    gameobject.has_sfx = settings_node.child("AUDIO").attribute("sfx").as_bool();

    //- Finally, setup document
    gameobject.doc.load_file(path.c_str());
    gameobject.settings_node = gameobject.doc.child("settings");
}

void Game::create_files(int state)
{
	auto create_config_file = [this]() -> void
	{
		pugi::xml_document file;
		sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
		pugi::xml_node settings_node = file.append_child("settings");

		pugi::xml_node windim = settings_node.append_child("DIMENSIONS-WINDOWED");
		windim.append_attribute("width") = 860;
		windim.append_attribute("height") = 640;

		pugi::xml_node fulldim = settings_node.append_child("DIMENSIONS-FULLSCREEN");
		fulldim.append_attribute("width") = desktop.width;
		fulldim.append_attribute("height") = desktop.height;

		pugi::xml_node screennode = settings_node.append_child("SCREEN");
		screennode.append_attribute("fullscreen") = false;

		pugi::xml_node audionode = settings_node.append_child("AUDIO");
		audionode.append_attribute("music") = true;
		audionode.append_attribute("sfx") = true;

		pugi::xml_node controls = settings_node.append_child("CONTROLS");
		controls.append_attribute("standard-movement") = true;

		std::string str = gameobject.appdata+"settings.xml";
		// file.print(std::cout);
		file.save_file(str.c_str());
	};

	auto create_save_file = [this]() -> void
	{
		//@TODO: Save file creation
	};

	#define BOTH 3
	#define SAVE 2
	#define CONFIG 1

	switch(state)
	{
		case SAVE:
			create_save_file();
		break;
		case CONFIG:
			create_config_file();
		break;
		case BOTH:
			create_config_file();
			create_save_file();
		break;
		default:
		break;
	}

	#undef CONFIG
	#undef SAVE
	#undef BOTH
}

int Game::has_files()
{
	bool has_save = true, has_config = true;

	//- check for savegame file existence
	std::ifstream savefile;
	std::string savepath = gameobject.appdata+"\\savefile.txt";
	savefile.open(savepath);
	if(!savefile.is_open()){
		std::cout << "File not found:" << savepath << "\n";
		has_save = false;
	}

	//- check for xml existence
	pugi::xml_document tmp2;
	std::string str = gameobject.appdata+"settings.xml";
   	if(!tmp2.load_file(str.c_str())){
   		std::cout << "File not found: " << gameobject.appdata+"settings.xml" << "\n";
   		has_config = false;
   	}
   	else{
   		gameobject.doc.load_file(str.c_str());
   		gameobject.settings_node = gameobject.doc.child("settings");
   	}

   	if(!has_save && !has_config)
   		return 3;
   	else if(!has_save)
   		return 2;
   	else if(!has_config)
   		return 1;

	return 0;
}

void Game::handle_events(sf::Event ev)
{
	while(window.pollEvent(ev))
	{
		//- Handle state events first, then general states.
		state_stack.back()->handle_events(this, ev);
		switch(ev.type)
		{
			case sf::Event::Closed:
			{
				// window.close();
				quit();
			}break;
			default:
			break;
		}
	}
}

void Game::update(sf::Time dt)
{
	//- Update current state
	state_stack.back()->update(this, dt);
}

void Game::render(sf::RenderWindow &window)
{
	window.clear();
	state_stack.back()->render(this);
	window.display();
}

void Game::change_state(State* state)
{
	//- Cleanup current state
	if(!state_stack.empty()){
		state_stack.back()->cleanup();
		state_stack.pop_back();
	}

	//- Store new state
	state_stack.push_back(state);
	state_stack.back()->init(this);
}

void Game::push_state(State* state)
{
	//- Pause current state
	if(!state_stack.empty()){
		state_stack.back()->pause();
	}

	//- Store new state
	state_stack.push_back(state);
	state_stack.back()->init(this);
}

void Game::pop_state()
{
	//- Cleanup current state
	if(!state_stack.empty()){
		state_stack.back()->cleanup();
		state_stack.pop_back();
	}

	//- Resume previous state
	if(!state_stack.empty()){
		state_stack.back()->resume();
	}
}

void Game::run()
{
	init();
	push_state(IntroState::instance());

	while(is_running)
	{
		sf::Event event;
		handle_events(event);
		update(clock.restart());
		render(window);
	}
}
