#include "GamePath.hpp"

namespace GamePath{
    std::string Root;
    std::string Level;
    std::string Animation;
    std::string Music;
    std::string Sound;
    std::string Tileset;

    void GeneratePath(){
        Level=Root+"\\Resources\\Levels\\";
        Animation=Root+"\\Resources\\Animations\\";
        Music=Root+"\\Resources\\Musics\\";
        Sound=Root+"\\Resources\\Sounds\\";
        Tileset=Root+"\\Resources\\Tilesets\\";
    }
};
