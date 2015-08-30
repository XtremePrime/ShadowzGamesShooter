#include "hud.h"

Hud::Hud(sf::Font f, int w, int h)
{
	init(f, w, h);
}

void Hud::init(sf::Font f, int w, int h)
{
	this->font = f;
	this->screen_height = h;
	this->screen_width = w;

	//- Health bar init
	hpbar_txr.loadFromFile("res/screen/healthbar/hp_0.png");
	hpbar.setTexture(hpbar_txr);

	//- Init score
	score_txt.setPosition(200, 200);
	score_txt.setCharacterSize(15);
	score_txt.setFont(font);
	score_txt.setColor(sf::Color::White);
	score_txt.setString("Score: 0");
}

void Hud::update(sf::Time deltaTime, Player& player, Level& level)
{
	{
		std::ostringstream ss;
		ss << "res/screen/healthbar/hp_";
		ss << player.get_hp();
		ss << ".png";
		if(!hpbar_txr.loadFromFile(ss.str()))
			hpbar_txr.loadFromFile("res/screen/healthbar/hp_0.png");
	}
	{
    	std::ostringstream ss;
    	ss << "Score: " << player.get_score();
    	score_txt.setString(ss.str());
	}

	#define t(xr,yr) 5+(xr)-(yr/2)
	// sprite.setPosition(t(player.get_x(), level.get_view().getSize().x), t((player.get_y()+screen_height)-HEIGHT*SCALE, level.get_view().getSize().y));
	hpbar.setPosition(t((player.get_x()+screen_width)-280, level.get_view().getSize().x), t((player.get_y()+screen_height)-35, level.get_view().getSize().y));
	score_txt.setPosition(t(player.get_x(), level.get_view().getSize().x), t(player.get_y(), level.get_view().getSize().y));
	#undef t
}

void Hud::render(sf::RenderWindow* win)
{
	win->draw(hpbar);
	win->draw(score_txt);
}
