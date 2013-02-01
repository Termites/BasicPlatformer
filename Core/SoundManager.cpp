#include "SoundManager.hpp"

void SoundManager::Tick()
{
	for (std::list<Sound>::iterator it = SoundList.begin();it!=SoundList.end();
		++it)
	{
		Sound & S = *it;
		sf::Sound::Status SState = S.Source.GetStatus(); // sf::Sound::Playing sf::Sound::Paused sf::Sound::Stopped

		if (SState == sf::Sound::Stopped)
			S.Playing=false;
	}

	if (SoundList.size()>0)
	{
		Sound S = SoundList.back();
		while (S.Playing==false && SoundList.size()>0)
		{
			SoundList.pop_back();
			S = SoundList.back();
		}
	}
}

Sound& SoundManager::PlaySound(const sf::SoundBuffer & Buffer,bool Loop)
{
	Sound  & NewSound = GetSlot();

	NewSound.Source.SetBuffer(Buffer);
	NewSound.Playing=true;
	NewSound.Loop = Loop;
	NewSound.Source.SetLoop(Loop);
	NewSound.Source.Play();


	return NewSound;
}

Sound& SoundManager::GetSlot()
{
	for (std::list<Sound>::iterator it = SoundList.begin();it!=SoundList.end();
		++it)
	{
		Sound & S = *it;
		if (S.Playing == false)
			return S;
	}

	SoundList.resize(SoundList.size()+1);
	Sound&S = SoundList.back();
	return S;
}
