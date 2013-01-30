#pragma once
#include<SFML/Audio.hpp>
#include <String>
#include <List>

template<typename T>
struct Resource
{
	std::string Name;
	T Value;
};

inline char Lower(char C)
{
    return C >='A' && C<='Z' ? C+32 : C;
}

class ResourceManager
{
	private:
		std::list<Resource<sf::SoundBuffer>> SoundList;
	public:
		sf::SoundBuffer & LoadSound(const std::string & S);

};

