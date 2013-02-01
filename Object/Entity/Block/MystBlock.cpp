#include "MystBlock.hpp"

extern ResourceManager R;

MystBlock::MystBlock(const vec2i &Location) : TileEntity(Location){
    Spr=R.LoadSprite("MystBlock",vec2i(16,16));
    //Anims=R.LoadAnim("MystBlock");
    //PlayAnim("idle");
    Activated=false;
}

void MystBlock::OnTileChangement(const Tile &New){}
