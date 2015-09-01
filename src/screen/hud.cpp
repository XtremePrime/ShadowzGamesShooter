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

	//- Init text
	score.init(font, "Score", sf::Vector2f(0, 0));
	wave.init(font, "Wave", sf::Vector2f(100, 100));
	enemies_left.init(font, "Left", sf::Vector2f(200, 200));
}

void Hud::update(sf::Time deltaTime, Player& player, Level& level, int cur_w, int el)
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
    	score.setString(ss.str());
	}
	{
    	std::ostringstream ss;
    	ss << "Wave: " << cur_w;
    	wave.setString(ss.str());
	}
	{
		std::ostringstream ss;
    	ss << "Left: " << el;
    	enemies_left.setString(ss.str());
	}

	#define set_x(xr) 5+(xr)-(level.get_view().getSize().x/2)
	#define set_y(yr) 5+(yr)-(level.get_view().getSize().y/2)
	// hpbar.setPosition(t((player.get_x()+screen_width)-280, level.get_view().getSize().x), t((player.get_y()+screen_height)-35, level.get_view().getSize().y));
	score.setPosition(set_x(player.get_x()+0), set_y(player.get_y()+0));
	wave.setPosition(set_x(player.get_x()+275), set_y(player.get_y()+0));
	enemies_left.setPosition(set_x(player.get_x()+425), set_y(player.get_y()+0));
	hpbar.setPosition(set_x(player.get_x()+280), set_y((player.get_y()+screen_height)-35));
	#undef set_y
	#undef set_x
}

void Hud::render(sf::RenderWindow* win)
{
	win->draw(hpbar);
	wave.render(win);
	score.render(win);
	enemies_left.render(win);
}
