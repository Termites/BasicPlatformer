#pragma once
#include<SFML/Audio.hpp>
#include<List>
struct Sound
{
	sf::Sound Source;
	bool Playing;
	bool Loop;
};

class SoundManager
{
	private:
		std::list<Sound> SoundList; // Liste des sons joués

		Sound & GetSlot();

	public:

		void Tick();
		//@Param Buffer : Le son à jouer
		//@Param Loop  : Si on le boucle
		Sound& PlaySound(const sf::SoundBuffer & Buffer,bool Loop=false);

};
