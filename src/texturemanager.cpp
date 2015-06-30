#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "texturemanager.h"

void TextureManager::load_texture(const std::string& name, const std::string& path)
{
	sf::Texture tx;
	tx.loadFromFile(path);

	textures[name] = tx;
}

sf::Texture& TextureManager::get_ref(const std::string& texture)
{
	return this->textures.at(texture);
}