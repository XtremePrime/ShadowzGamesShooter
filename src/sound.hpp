#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>
#include <sstream>

class Sound
{
private:
	sf::Sound sound;
	sf::SoundBuffer buffer;
public:
	void init(std::string filename)
	{
		{
			std::ostringstream ss;
			ss << "res/sfx/";
			ss << filename;
			buffer.loadFromFile(ss.str());
		}
		sound.setBuffer(buffer);
	}

	void play(){sound.play();}
	void pause(){sound.pause();}
	void stop(){sound.stop();}
	void setLoop(bool loop){sound.setLoop(loop);}
};

#endif // SOUND_H
