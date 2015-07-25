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
	this->has_sfx = game->get_gameobject()->has_sfx;

	//- Binding to the port to establish connection
	if (socket.bind(port) != sf::Socket::Done)
		std::cout << "Could not connect to: " << "localhost" << "!\n";

	// char data[] = "abc";
	// if (socket.send(data, 3, game->get_gameobject()->ip_address, game->get_gameobject()->port) != sf::Socket::Done)
	// {
   		// std::cout << "Sent bby\n";
	// }

	level.init("res/levels/demons/");
	player.init(game->get_gameobject(), 400, 400, 32, 32);
	// mobs.push_back(new Mob(150, 150, 16, 32));
	mob.init(150, 150, 32, 32);

	// mob.init(150, 150, 16, 32);


	//- Music & Sound init
	music.openFromFile("res/music/devtest.flac");
	music.setLoop(true);
	if(game->get_gameobject()->has_music)
		music.play();

	shoot_buf.loadFromFile("res/sfx/shootgun.wav");
	shoot_snd.setBuffer(shoot_buf);

	//- UI init
	font.loadFromFile("res/fonts/PressStart2P.ttf");
	score_txt.setPosition(200, 200);
	score_txt.setCharacterSize(15);
	score_txt.setFont(font);
	score_txt.setColor(sf::Color::White);
	score_txt.setString("Score: 0");

	game->get_window()->setView(level.get_view());
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
    		if(has_sfx)
    			shoot_snd.play();

    		player.update_score(100);
    		std::stringstream ss;
    		ss << "Score: " << player.get_score();
    		score_txt.setString(ss.str());
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
		player.handle_events(&event);
	}
}

void GameState::update(Game* game,  sf::Time deltaTime)
{
	//- update EVERYTHING
	if(is_paused){return;}
	level.update(deltaTime);
	player.update(deltaTime);
	for(Mob* mob : mobs){
		mob->update(deltaTime);
	}
	for(Bullet* bullet : bullets){
		bullet->update(deltaTime);
	}

	//- Update player movement
	float f = deltaTime.asSeconds();
	#define t(xx, yy) xx+(yy*f)
	// std::cout << t(player.get_x(),player.get_vx()) << "!!" << t(player.get_y(),player.get_vy()) << "\n";
	if(!level.is_oob(player.get_x(), player.get_y())){
		if( player.can_move( level.get_tile( t(player.get_y(),player.get_vy()),t(player.get_x(),player.get_vx()) ) ) ){
			player.set_lx(player.get_x());
			player.set_ly(player.get_y());
			player.move2(player.get_vx(), player.get_vy(), deltaTime);
		}
	}else{
		player.set_x(player.get_lx());
		player.set_y(player.get_ly());
		std::cout << "OOB!\n";
	}

	#undef t

	//- Check deletation of mobs
	if(mobs.size() > 0)
	{
		for(int i = 0; i < mobs.size(); ++i){
			if(mobs[i]->removed)
			{
				std::cout << "Deleting mob: " << i << "\n";
				player.update_score(mobs[i]->get_points());
				mobs[i] = nullptr;
				mobs.erase(mobs.begin()+i);
			}
		}
	}

	//- Check collision of bullets w/ mobs & deletation
	if(bullets.size() > 0)
	{
		for(Bullet* bullet : bullets)
		{
			if(mob.intersects(*bullet))
			{
				bullet->remove();
				mob.damage(1);
				std::cout << mob.get_hp() << "\n";
			}
		}
		for(int i = 0; i < bullets.size(); ++i){
			if(bullets[i]->removed)
			{
				// std::cout << "Deleting bullet: " << i << "\n";
				bullets[i] = nullptr;
				bullets.erase(bullets.begin()+i);
			}
		}
	}

	if(mob.intersects (player)){
       player.hp -= mob.dmg;
       std::cout <<"Player hp "<<player.hp <<"\n";
	}



	//- Player rotation based on mouse loc
	rotate(&player, game, deltaTime);
	#define t(xr,yr) 5+xr-(yr/2)
	score_txt.setPosition(t(player.get_x(), level.get_view().getSize().x), t(player.get_y(), level.get_view().getSize().y));
	#undef t

	//- Rotate mobs towards player loc.$
	rotate2(&mob, game, deltaTime, sf::Vector2i(player.get_x(), player.get_y()));

	//- Collision test!
	// if(player.intersects(mob))
	// 	std::cout << "Collision!\n";
	mob.update(deltaTime);
    mob.move2(player.get_x(), player.get_y());
    player.update(deltaTime);
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
	level.render(game->get_window(), player.get_x(), player.get_y(), game->get_gameobject()->width, game->get_gameobject()->height);
	game->get_window()->setView(level.get_view());
	player.render(game->get_window());
	for(Mob* mob : mobs){
		mob->render(game->get_window());
	}
	for(Bullet* bullet : bullets){
		bullet->render(game->get_window());
	}

    mob.render(game->get_window());

	//- UI stuff is rendered over everything else
	game->get_window()->draw(score_txt);
}


void GameState::cleanup()
{
	clear_vector(mobs);
	clear_vector(bullets);

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
