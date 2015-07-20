#include "levelgen.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

void LevelGen::init(std::string path)
{
	this->path = path;

	txmgr.load_texture("floor.png", this->path+"floor.png");
	txmgr.load_texture("wall.png", this->path+"wall.png");

	grab_custom_tiles();
}

/*
* SCHEME:
* White and Black are both const colors allocated their certain filenames:
* White: Floor tiles (walkable) [floor.png]
* Black: Walls/Barrier (non-walkable) [wall.png]
* 
* To declare customs, create a "custom_tiles.txt" file in the level folder
* and fill it after the following schema:
* <filename> <Red> <Green> <Blue> <Alpha>
* lava.png 255 0 0 255
* TIP: Keep alpha at 255, to avoid problems in the future
*/

void LevelGen::generate_map()
{
	typedef std::map<std::string, sf::Color*>::iterator it_type;

	//- map is always named map.png in the level folder
	sf::Image map;
	map.loadFromFile(this->path+"map.png");

	size = map.getSize();

	sf::Clock timer;
	for(int i = 0; i < size.x*size.y; ++i)

	{
		int x = (int)i%size.x, y = (int)floor(i/size.x);
		sf::Color color = map.getPixel(x, y);

		//- Set tiles based on colors in the map
		if(is_color(color, 255, 255, 255))
			tiles.push_back(new Tile(x, y, false, txmgr.get_ref("floor.png")));
		else if(is_color(color, 0, 0, 0))
			tiles.push_back(new Tile(x, y, true, txmgr.get_ref("wall.png")));
		else{
			if(custom_tiles.size() < 1){continue;}
			for(it_type iterator = custom_tiles.begin(); iterator != custom_tiles.end(); iterator++)
			{
				if(is_color(color, (int)iterator->second->r, (int)iterator->second->g, (int)iterator->second->b))
					tiles.push_back(new Tile(x, y, txmgr.get_ref(iterator->first)));
			}
		}
	}

	std::cout << "Level constructed in [" << timer.restart().asMilliseconds() << "] with a total of [" << tiles.size() << "] tiles\n";

}

void LevelGen::grab_custom_tiles()
{
	std::ifstream file;
	file.open(this->path+"custom_tiles.txt");
	if(!file.is_open()){std::cout << "File couldn't be open.\n";return;}
	if(file.peek() == std::ifstream::traits_type::eof()){std::cout<<"Custom tiles file is empty!\n";return;}

	while(!file.eof())
	{
		std::string line, name;
		sf::Color temp_col;

		std::getline(file, line);

		//- Handle actual code by splitting it into tokens
		std::vector<std::string> tokens;
		//- We use a lambda expr to split the line
		auto split = [&tokens](std::string input) -> void
		{
			int pos = 0;

			for(int i = 0; i < input.length(); ++i)
			{
				//- If any of these delimiters is found, we split
				if(input[i] == ' ' || input[i] == '\n' || input[i] == '\0')
				{
					std::string x = input.substr(pos, i-pos);
					//- Only push if the string is not empty!
					if(!input.substr(pos, i-pos).empty())
						tokens.push_back(input.substr(pos, i-pos));
					pos = i+1;
				}

			}

			//- Considering we don't end with a space, we need to push one last time
			std::string x = input.substr(pos, input.length()-pos);
    		if(!x.empty())
       	 		tokens.push_back(x);
		};
		split(line);

		#define NAME tokens[0]
		#define R tokens[1]
		#define G tokens[2]
		#define B tokens[3]
		#define A tokens[4]

		custom_tiles[NAME] = new sf::Color(atoi(R.c_str()),atoi(G.c_str()),atoi(B.c_str()),atoi(A.c_str()));

		#undef NAME
		#undef R
		#undef G
		#undef B
		#undef A

		//- Load the new custom tile name into the texture as a full string ("lava.png")
		txmgr.load_texture(tokens[0], this->path+tokens[0]);

		// std::cout << "(" << (int)custom_tiles["ground.png"]->r << "," << (int)custom_tiles["ground.png"]->g << "," << (int)custom_tiles["ground.png"]->b << "," << (int)custom_tiles["ground.png"]->a << ")\n";
	}
	file.close();
}

//- Check if a color follows an RGB
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
