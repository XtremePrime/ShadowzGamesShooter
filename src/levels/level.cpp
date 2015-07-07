#include "level.h"
#include "levelgen.h"

void Level::init(std::string filepath)
{
	gen.init(filepath);
	gen.generate_map();

	view.reset(sf::FloatRect(0, 0, 860, 640));

	TOTAL_TILES = gen.get_tiles().size();
}

void Level::handle_events(sf::Event *event)
{

}

void Level::render(sf::RenderWindow *window, int xp, int yp)
{
	window->setView(view);

	sf::Clock timer;
	
	//- XP and YP is the position of the player
	//- PosX and PosY is the position of the screen
	int posx = xp + 10 - (view.getSize().x/2);
	int posy = yp + 10 - (view.getSize().y/2);

	int count = 0;

	//- Rendering every tile that is visible to the current player.
	//- Also a few tiles that are not visible so that the game
	//- doesn't show black screens when removing tiles out of view.
	for(int i = 0; i < TOTAL_TILES; ++i)
	{
		// std::cout << "gen.get_tiles()[i]->get_x(): " << gen.get_tiles()[i]->get_x() << " / posx-32: " << posx-32 << " / view.getSize().x+32: " << view.getSize().x+32 << "\n"; 
		Tile *tile = gen.get_tile(i);
		if(!(tile->get_x() < posx-32*2) && !(tile->get_x() > view.getSize().x+posx+32*2) &&
			!(tile->get_y() < posy-32*2) && !(tile->get_y() > view.getSize().y+posy+32*2))
		{
			count++;
			tile->render(window);
		}
	}
	
	// std::cout << "It took [" << timer.restart().asMilliseconds() << "] ms to render  [" << count << "] from [" << TOTAL_TILES << "] total tiles\n";

	view.reset(sf::FloatRect(posx, posy, 860, 640));
}

void Level::update(sf::Time deltaTime)
{

	for(int i = 0; i < TOTAL_TILES; ++i){
		gen.get_tile(i)->update(deltaTime);
	}

}

Tile* Level::get_tile(int x, int y)
{
	sf::Vector2u size = gen.get_map_size();
	int xa = (x/32)-1;
	int ya = (y/32)-1;
	return gen.get_tiles()[xa * size.x + ya];
}
