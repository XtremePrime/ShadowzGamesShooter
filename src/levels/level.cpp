#include "level.h"
#include "levelgen.h"

void Level::init(std::string filepath)
{
	gen.init(filepath);
	gen.generate_map();
}

void Level::render(sf::RenderWindow *window)
{
	for(int i = 0; i < gen.get_tiles().size(); ++i){
		// std::cout << gen.get_tiles()[i]->get_x() << "/" << gen.get_tiles()[i]->get_y() << "\n";
		gen.get_tiles()[i]->render(window);
	}
}

void Level::update(sf::Time deltaTime)
{
	/*for(int i = 0; i < gen.get_tiles().size(); ++i){
		// std::cout << gen.get_tiles()[i]->get_x() << "/" << gen.get_tiles()[i]->get_y() << "\n";
		gen.get_tiles()[i]->update(deltaTime);
	}*/
}
