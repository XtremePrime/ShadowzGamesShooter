#include "spawnpointlist.h"

void SpawnPointList::init(std::string path)
{
	this->path = "res/levels/"+path+"/spawnpoints.txt";
	load_file(this->path);
	timer.restart();
}

void SpawnPointList::load_file(std::string path)
{
	std::ifstream file;
	file.open(path);
	if(!file.is_open()){std::cout << "File couldn't be open.\n";return;}
	if(file.peek() == std::ifstream::traits_type::eof()){std::cout<<"Spawnpoints file is empty!\n";return;}

	while(!file.eof())
	{
		std::string line;

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
				if(input[i] == ' ' || input[i] == ',' || input[i] == '\n' || input[i] == '\0')
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

		#define X atoi(tokens[0].c_str())
		#define Y atoi(tokens[1].c_str())
		splist.push_back(new SpawnPoint(X, Y));
		spawn_count++;
		#undef X
		#undef Y
	}
}

SpawnPoint* SpawnPointList::get_sp(int xx, int yy)
{
	for(SpawnPoint* sp : splist)
		if(sp->get_x() == xx && sp->get_y() == yy)
			return sp;
	return nullptr;
}

void SpawnPointList::cleanup()
{
	for(int i = 0; i < splist.size(); ++i)
		delete (splist[i]);
 	splist.clear();
}
