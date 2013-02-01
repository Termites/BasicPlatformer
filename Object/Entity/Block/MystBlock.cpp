#include "MystBlock.hpp"

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
    if(!Activated){
        PlayAnim("activated");
        Physic=PHYS_Falling;
        Velocity.y=-3;
        Activated=true;
    }
}

void MystBlock::OnAnimEnd(){
    if(Activated) PlayAnim("deactivated");
}

void MystBlock::Tick(){
    if(Activated && Velocity.y>0 && Location.y+Velocity.y>=TileLocation.y*16){
        Physic=PHYS_None;
        Location.y=TileLocation.y*16;
        Velocity.y=0;
    }
    TileEntity::Tick();
}
