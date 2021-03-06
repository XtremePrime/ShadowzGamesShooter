#include <string>
#include <SFML/Network.hpp>
#include "pugixml.hpp"

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
public:
	//- Setting objects
	pugi::xml_document doc;
	pugi::xml_node settings_node;
	std::string appdata;

	//- Network objects
	sf::IpAddress ip_address = "127.0.0.1";
	unsigned short port = 7777;
	bool is_multiplayer = false;

	//- Level objects
	std::string level_name = "devtest";
	int wave = 0;
	int score = 0;

	//- Options objects
	int width = 860, height = 640;
	bool is_fullscreen = false;
	bool is_standard_movement = true;
	bool has_music = true;
	bool has_sfx = true;
	float volume = 1.0;
	std::string version = "DEMO";
	std::string username = "Demo Player";
};

#endif // GAMEOBJECT_H
