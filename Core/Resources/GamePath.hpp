#pragma once
#include <string>

/*
	Namespace that contains all the path required for resources : 
*/


namespace GamePath
{
	extern std::string Root;

	extern std::string Level;

	extern std::string Animation;
	
	extern std::string Music;
	extern std::string Sound;
	extern std::string Tileset;

	// Generate every path from Root one : 
	void GeneratePath();
};