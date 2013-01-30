#include "ResourceManager.hpp"
#include "GamePath.hpp"
#include<iostream>
#include<algorithm>

sf::SoundBuffer & ResourceManager::LoadSound(const std::string&Snd)
{
			std::string LowerName;
			LowerName.resize(Snd.size());
			std::transform(Snd.begin(),Snd.end(),LowerName.begin(),Lower);

			// On vérifie que le son n'est pas déjà chargé :

			for (auto it = SoundList.begin();it!=SoundList.end();++it)
			{
				Resource<sf::SoundBuffer> & R = *it;

				if (R.Name == LowerName)
					return R.Value;
			}


			SoundList.resize(SoundList.size()+1);

			Resource<sf::SoundBuffer> &R = SoundList.back();
			R.Name = LowerName;
			R.Value.LoadFromFile(GamePath::Sound+Snd+".wav");

			return R.Value;
}
