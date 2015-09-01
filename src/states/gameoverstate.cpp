#include "gameoverstate.h"

GameOverState* GameOverState::_instance;

GameOverState* GameOverState::instance(){
	if(_instance == NULL)
		_instance = new GameOverState();
	return _instance;
}

void GameOverState::init(Game* game)
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

	menu_options[0]->setString("CONTINUE");
	menu_options[1]->setString("END");

	//- Init selector
	selector.setSize(sf::Vector2f(14, 14));
	selector.setFillColor(sf::Color::White);

	//- Init titlescreen
	ts_txr.loadFromFile("res/screen/game_over.png");
	title_screen.setTexture(ts_txr);
	title_screen.scale(1.4f, 1.1f);
	{
		sf::FloatRect ts_box = title_screen.getLocalBounds();
		title_screen.setOrigin(ts_box.left+ts_box.width/2.0f,ts_box.top+ts_box.height/2.0f);
		title_screen.setPosition(GAME_WIDTH/2.0f, 50+(285*1.1f)/2);
	}

	for(int i = 0; i < MAX_OPTIONS; ++i)
		menu_options[i]->setPosition(GAME_WIDTH/2-MENU_OFFSET_X, (i*32)+(GAME_HEIGHT/2)+MENU_OFFSET_Y);
	selector.setPosition(GAME_WIDTH/2-MENU_OFFSET_X-24, (selected_id*32)+(GAME_HEIGHT/2)+MENU_OFFSET_Y);

	music_delay.restart();
	music.openFromFile("res/music/gameover.wav");
	music.setLoop(true);
	if(game->get_gameobject()->has_music){
		music.setVolume(game->get_gameobject()->volume);
		// music.play();
	}

	auto init_text = [this](sf::Text& t, sf::Font& f, std::string title, sf::Vector2f vec) -> void
	{
		t.setCharacterSize(25);
		t.setFont(f);
		t.setColor(sf::Color::White);
		t.setString(title);
	};
	init_text(review, font, "test", sf::Vector2f(270, GAME_HEIGHT/2.0f));
	{
		std::ostringstream ss;
		ss << "Score: ";
		ss << game->get_gameobject()->score;
		ss << "| Wave: ";
		ss << game->get_gameobject()->wave;
		review.setString(ss.str());
	}
	sf::FloatRect box = review.getLocalBounds();
	review.setOrigin(box.left + box.width/2.0f, box.top  + box.height/2.0f);
	review.setPosition(GAME_WIDTH/2.0f, GAME_HEIGHT/2.0f);
}

void GameOverState::move_selected(bool up)
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

	selector.setPosition(GAME_WIDTH/2-MENU_OFFSET_X-24, (selected_id*32)+(GAME_HEIGHT/2)+MENU_OFFSET_Y);

}

void GameOverState::handle_events(Game* game, sf::Event event)
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
					case 0: //- Continue
						music.stop();
						game->change_state(GameState::instance()); 
					break;
					case 1: //- End
						music.stop();
						game->change_state(IntroState::instance());
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
void GameOverState::update(Game* game, sf::Time deltaTime)
{
	if(music_delay.getElapsedTime().asSeconds() >= 1.0f && music.getStatus() != sf::Music::Playing)
		music.play();
}
void GameOverState::render(Game* game)
{
	game->get_window()->draw(title_screen);
	for(int i = 0; i < menu_options.size(); ++i)
		game->get_window()->draw(*menu_options[i]);
	game->get_window()->draw(selector);
	game->get_window()->draw(review);
}

void GameOverState::cleanup()
{
	for(int i = 0; i < menu_options.size(); ++i)
		delete (menu_options[i]);
	menu_options.clear();
	_instance = NULL;
}

void GameOverState::pause()
{

}
void GameOverState::resume()
{

}