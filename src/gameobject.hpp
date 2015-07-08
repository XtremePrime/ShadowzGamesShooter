#include <string>
#include <SFML/Network.hpp>

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
private:
public:
	//Setting default values

	//- Network objects
	sf::IpAddress ip_address = "127.0.0.1";
	unsigned short port = 7777;
	bool is_multiplayer = false;
	bool is_fullscreen = false;
	bool is_standard_movement = true;

	//- Level objects
	std::string level_name = "devtest";

	//- Options objects
	int width = 860, height = 640;
	std::string version = "v0.2_3";
};

#endif // GAMEOBJECT_H