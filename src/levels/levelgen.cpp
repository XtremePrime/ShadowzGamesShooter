#include "levelgen.h"

void LevelGen::init(std::string path)
{
	this->path = path;
}

/*
* COLOR SCHEME:
* White: Floor tiles (walkable) [floor.png]
* Black: Walls/Barrier (non-walkable) [wall.png]
* Red, Blue, Green, Purple: (???) [tile1.png, tile2.png...]
*/

void LevelGen::generate_map()
{
	//- map is always named map.png in the level folder
	sf::Image map;
	map.loadFromFile(this->path+"map.png");

	sf::Vector2u size = map.getSize();

	for(int y = 0; y < size.y; ++y)
	{
		for(int x = 0; x < size.x; ++x)
		{
			//- Grab 1 pixel at a time
			sf::Color color = map.getPixel(x, y);

			//- Set tiles based on colors in the map
			if(is_color(color, 255, 255, 255))
				tiles.push_back(new Tile(x, y, this->path+"floor.png"));
			else if(is_color(color, 0, 0, 0))
				tiles.push_back(new Tile(x, y, this->path+"wall.png"));
			
			// std::cout << "Hello @" << x << "," << y << "(" << (int)color.r << "," << (int)color.g << "," << (int)color.b << "," << (int)color.a << ")\n";
		}
	}
}

bool LevelGen::is_color(sf::Color color, uint8_t r, uint8_t g, uint8_t b)
{
	if(color.r == r && color.g == g && color.b == b)
		return true;
	return false;
}

bool LevelGen::is_alpha(sf::Color color, uint8_t a)
{
	if(color.a == a)
		return true;
	return false;
}