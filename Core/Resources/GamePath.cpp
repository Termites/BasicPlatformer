#include "GamePath.hpp"


namespace GamePath
{
	std::string Root;

	std::string Level;

	std::string Animation;

	std::string Music;
	std::string Sound;
	std::string Tileset;

	void GeneratePath()
	{
		Level = Root+"\\Content\\Levels\\";

		Animation = Root+"\\Content\\Animations\\";

		Music = Root+"\\Content\\Music\\";

		Sound = Root+"\\Content\\Sounds\\";

		Tileset = Root+"\\Content\\Tilesets\\";

	}
};
