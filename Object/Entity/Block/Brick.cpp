#include "Bricks.hpp"
#include "Brick.hpp"

extern ResourceManager R;

Brick::Brick(const vec2i &Location) : TileEntity(Location){
    this->Location=Location*16;
    Spr=R.LoadSprite("Brick",vec2i(16,16));
    Anims=R.LoadAnim("Brick");
    PlayAnim("idle");
    Broken=false;
}

void Brick::OnTileChangement(const Tile &New){
    Level->SetBlockAt(TileLocation,Tile(0,false));
    if(!Broken){
        Level->RegisterObject(new Bricks(this->GridLocation,vec2f(-2,-4)));
        Level->RegisterObject(new Bricks(this->GridLocation,vec2f(2,-4)));
        Level->RegisterObject(new Bricks(this->GridLocation,vec2f(-2,-8)));
        Level->RegisterObject(new Bricks(this->GridLocation,vec2f(2,-8)));
        Level->DeleteObject(this);
        Broken=true;
    }
}