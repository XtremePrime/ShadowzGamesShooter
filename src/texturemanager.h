#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class TextureManager{
private:
	std::map<std::string, sf::Texture> textures;
protected:
public:
	TextureManager(){}
	~TextureManager(){}

	void load_texture(const std::string&, const std::string&);
	sf::Texture& get_ref(const std::string&);
};

#endif // TEXTUREMANAGER_H