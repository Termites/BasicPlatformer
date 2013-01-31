#include<iostream>
#include<algorithm>
#include "ResourceManager.hpp"
#include "GamePath.hpp"

sf::SoundBuffer &ResourceManager::LoadSound(const std::string &Snd){
    std::string LowerName;
    LowerName.resize(Snd.size());
    std::transform(Snd.begin(),Snd.end(),LowerName.begin(),Lower);
    for (auto it=SoundList.begin(); it!=SoundList.end(); ++it){
        Resource<sf::SoundBuffer> &R=*it;
        if(R.Name==LowerName) return R.Value;
    }
    SoundList.resize(SoundList.size()+1);
    Resource<sf::SoundBuffer> &R=SoundList.back();
    R.Name=LowerName;
    R.Value.LoadFromFile(GamePath::Sound+Snd+".wav");
    return R.Value;
}
