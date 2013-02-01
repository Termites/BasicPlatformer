#pragma once
#include<SFML/Audio.hpp>
#include<List>

struct Sound{
	sf::Sound Source;
	bool Playing;
	bool Loop;
};

class SoundManager{
	private:
		std::list<Sound> SoundList;
		Sound &GetSlot();

	public:
		void Tick();
		Sound &PlaySound(const sf::SoundBuffer &Buffer, bool Loop);

    protected:
};
