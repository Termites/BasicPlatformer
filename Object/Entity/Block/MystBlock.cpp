#include "MystBlock.hpp"
#include <iostream>

extern ResourceManager R;

MystBlock::MystBlock(const vec2i &Location) : TileEntity(Location){
    this->Location=Location*16;
    Spr=R.LoadSprite("MystBlock",vec2i(16,16));
    Anims=R.LoadAnim("MystBlock");
    PlayAnim("idle");
    Activated=false;
}

void MystBlock::OnTileChangement(const Tile &New){
    Level->SetBlockAt(TileLocation,Tile(0,true));
    PlayAnim("activated");
    Physic=PHYS_Falling;
    Velocity.y=-8;
    Activated=true;
    std::cout << "a" << std::endl;
}
