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

	//- Init Level
	level.init("res/levels/"+game->get_gameobject()->level_name+"/");

	//- Init player
	//Always spawn the player in the middle of the map
	player.init(game->get_gameobject(), (level.get_map_size().x*32)/2-32/2, (level.get_map_size().y*32)/2-32/2, 25, 31);
	player.set_weapon(Weapon::WeaponEnum::M4A1);


	//- Music & Sound init
	music.openFromFile("res/music/"+game->get_gameobject()->level_name+"/theme.flac");
	music.setLoop(true);
	if(game->get_gameobject()->has_music)
		music.play();

	shoot_buf.loadFromFile("res/sfx/shootgun.wav");
	shoot_snd.setBuffer(shoot_buf);

	//- UI init
	font.loadFromFile("res/fonts/PressStart2P.ttf");
	hud.init(font, game->get_gameobject()->width, game->get_gameobject()->height);

	//- Enemies setup
	splist.init(game->get_gameobject()->level_name);
	wave = 0;
	enemies_left = 0/*wave*5+wave*/;


	this->level_name = game->get_gameobject()->level_name;


	//- Setup game view
	game->get_window()->setView(level.get_view());
}

void GameState::player_shoot()
{
	#define ps(times) if(has_sfx){for(int i = 0; i < times; ++i){shoot_snd.play();}}

	switch(player.get_weapon().get_id())
	{
		case Weapon::WeaponEnum::PISTOL:
		case Weapon::WeaponEnum::M4A1:
		{
			//- One straight forward bullet, -1 from ammo, 1 sfx
			bullets.push_back(new Bullet(player.get_x(), player.get_y(), player.get_rotation(), player.get_weapon().get_dmg()));
			player.get_weapon().add_ammo(-1);
			ps(1);
		}
		break;
		case Weapon::WeaponEnum::SHOTGUN:
		{
			//- 3 spread bullets, -3 from ammo, 3 sfxs
			#define spread_angle 30
			bullets.push_back(new Bullet(player.get_x(), player.get_y(), player.get_rotation(), player.get_weapon().get_dmg()));
			bullets.push_back(new Bullet(player.get_x(), player.get_y(), player.get_rotation()+spread_angle, player.get_weapon().get_dmg()));
			bullets.push_back(new Bullet(player.get_x(), player.get_y(), player.get_rotation()-spread_angle, player.get_weapon().get_dmg()));
			player.get_weapon().add_ammo(-3);
			ps(1);
			#undef spread_angle
		}
		break;
		default:
			std::cout << "[GameState]: Error shooting weapon! Weird ID...\n";
		break;
	}

	#undef ps
}

void GameState::handle_events(Game* game, sf::Event event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		switch(event.key.code)
		{
			case sf::Keyboard::Escape:
			{
			}break;
			default:
			break;
		}
	}
	else if(event.type == sf::Event::MouseButtonPressed)
	{
		if(event.mouseButton.button == sf::Mouse::Left)
		{
			clicked = true;

    		// player.update_score(100);
		}
	}
	else if(event.type == sf::Event::MouseButtonReleased)
	{
		if(event.mouseButton.button == sf::Mouse::Left)
		{
			clicked = false;

			if(player.get_weapon().get_timer().getElapsedTime().asSeconds() >= player.get_weapon().get_delay())
    			player.get_weapon().get_timer().restart();
		}
	}
	else if(event.type == sf::Event::LostFocus)
	{
		pause();
	}
	else if(event.type == sf::Event::GainedFocus)
	{
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

	//- Spawn updater
	if(spawn_timer.getElapsedTime().asSeconds() >= 1.0f || left_to_spawn <= 0)
	{
		spawn_timer.restart();
		if(this->splist.get_spawn_count() < left_to_spawn)
			spawn_enemies(this->splist.get_spawn_count(), this->splist);
		else
			spawn_enemies(left_to_spawn, this->splist);
	}

	for(Mob* mob : mobs){
		mob->update(deltaTime);
	}
	for(Bullet* bullet : bullets){
		bullet->update(deltaTime);
	}

	//- Update player movement
	#define t(xx, yy) xx+(yy*(float)(deltaTime.asSeconds()))
	if(!level.is_oob(player.get_x(), player.get_y())){
		//- Player tile collision
		if( player.can_move( level.get_tile( t(player.get_y(),player.get_vy()),t(player.get_x(),player.get_vx()) ) ) ){
			player.set_lx(player.get_x());
			player.set_ly(player.get_y());
			player.move2(player.get_vx(), player.get_vy(), deltaTime, 0);
		}
	}else{ //- Player OOB handle
		player.set_x(player.get_lx());
		player.set_y(player.get_ly());
		std::cout << "OOB!\n";
	}
	#undef t

	//- Checking if the player is shooting
	if(clicked && player.get_weapon().get_timer().getElapsedTime().asSeconds() >= player.get_weapon().get_delay())
	{
		player.get_weapon().get_timer().restart();
		player_shoot();
	}

	//- Check deletation of mobs
	if(mobs.size() > 0)
	{
		for(Mob* mob: mobs)
		{
			//- MOB X TILE COLLISION TEST. REFACTOR ASAP
			//- COMMENT ASAP
			#define t(xx, yy) xx+(yy*(float)(deltaTime.asSeconds()))
			#define BOTH 0
			#define ONLY_X 1
			#define ONLY_Y 2
			bool state = false;
			if(mob->can_move( level.get_tile( mob->get_y()+(mob->get_vy()*(float)(deltaTime.asSeconds())), mob->get_x())))
			{
				// std::cout << "X2\n";
				mob->move2(mob->get_vx(), mob->get_vy(), deltaTime, ONLY_Y);
				state = true;
			}
			else if(mob->can_move( level.get_tile( mob->get_y()-(mob->get_vy()*(float)(deltaTime.asSeconds())), mob->get_x())))
			{
				// std::cout << "X2-2\n";
				mob->move2(mob->get_vx(), mob->get_vy(), deltaTime, ONLY_X);
				state = true;
			}
			if(mob->can_move( level.get_tile( mob->get_y(), mob->get_x()+(mob->get_vx()*(float)(deltaTime.asSeconds())))))
			{
				// std::cout << "X1\n";
				mob->move2(mob->get_vx(), mob->get_vy(), deltaTime, ONLY_X);
				state = true;
			}
			else if(mob->can_move( level.get_tile( mob->get_y(), mob->get_x()-(mob->get_vx()*(float)(deltaTime.asSeconds())))))
			{
				mob->move2(mob->get_vx(), mob->get_vy(), deltaTime, ONLY_Y);
				state = true;
			}
			if(!state){
				// std::cout << "X4\n";
				mob->move2(mob->get_vx(), mob->get_vy(), deltaTime, BOTH);
			}
			#undef BOTH
			#undef ONLY_X
			#undef ONLY_Y
			#undef t
		}

		//- Handle player X mob collision
		for(Mob* mob : mobs)
		{
			if(mob->intersects(player) && !player.is_invincible())
			{
				player.set_invincibility(true);
				player.get_inv_timer().restart();
				player.hurt(mob->get_dmg());
			}
		}

		for(int i = 0; i < mobs.size(); ++i){
			if(mobs[i]->removed)
			{
				std::cout << "Deleting mob: " << i << "\n";
				enemies_left--;
				player.update_score(mobs[i]->get_points());
				mobs[i] = nullptr;
				mobs.erase(mobs.begin()+i);
			}
		}
	}

	if(bullets.size() > 0)
	{
		//- Check if bullet intersects mob
		for(Bullet* bullet : bullets)
		{
			//- Check if bullets OOB
			if(level.is_oob(bullet->get_x(), bullet->get_y()))
				bullet->remove();

			//- Bullet x Tile collision
			#define t(xx, yy) xx+(yy*(float)(deltaTime.asSeconds()))
			if(!bullet->can_move( level.get_tile(bullet->get_y(), bullet->get_x())))
				bullet->remove();
			#undef t

			for(Mob* mob : mobs)
            {
                if(mob->intersects(*bullet))
                {
                    bullet->remove();
                    mob->hurt(bullet->get_dmg());
                	break;
                }
            }
		}
		for(int i = 0; i < bullets.size(); ++i){
			//- Bullet deletation
			if(bullets[i]->removed)
			{
				bullets[i] = nullptr;
				bullets.erase(bullets.begin()+i);
			}
		}
	}

	//- Change state on player death;
	if (player.get_death())
	{
		music.stop();
		game->get_window()->setView(game->get_window()->getDefaultView());
		game->change_state(GameOverState::instance());
	}

	//- Player rotation based on mouse loc
	rotate(&player, game, deltaTime);

	//- Rotate mobs towards player loc.$
	for(Mob* m : mobs)
		rotate2(m, game, deltaTime, sf::Vector2i(player.get_x(), player.get_y()));

    hud.update(deltaTime, player, level, wave, enemies_left);

    if(player.get_inv_timer().getElapsedTime().asSeconds() >= 1.0f)
    {
    	player.set_invincibility(false);
    }

    //- Check wave state & spawning
    if(enemies_left <= 0)
    {
    	++wave;
    	enemies_left = wave*5+wave;
    	left_to_spawn = enemies_left;
    }

	#define t(xr,yr,zr) (xr+zr)-(yr/2)
    // game->get_cursor()->setPosition(t(player.get_x(), level.get_view().getSize().x, game->get_cursor()->getPosition().x), t(player.get_y(), level.get_view().getSize().y, game->get_cursor()->getPosition().y));
    #undef t
}

void GameState::spawn_enemies(int amount, SpawnPointList& spl)
{
	for(int i = 0; i < amount; ++i)
		mobs.push_back(new BasicEnemy(spl.get_sp(i).get_x(), spl.get_sp(i).get_y(), 32, 32, this->level_name));
	left_to_spawn -= amount;
}

/*void GameState::check_weapon_pickup(Player& p)
{
	std::stringstream ss;
	ss << player.get_weapon().get_name() << "_pickup";
	if(p)

	if(player.get_weapon().get_name() == "strudel")
	{
		player.get_weapon().add_ammo(60);
	}
}*/

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

	//- UI stuff is rendered over everything else
	hud.render(game->get_window());
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
