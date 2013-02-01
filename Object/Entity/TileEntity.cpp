#include "TileEntity.hpp"
#include <iostream>


TileEntity::TileEntity(const vec2i &Location) : Entity(vec2i()){
    Entity(Location*16);
    TileLocation=Location;
    Physic=PHYS_None;
}

void TileEntity::Create(){
    Level->SetBlockAt(TileLocation,Tile(1,true));
}

void TileEntity::TileChanged(const vec2i &Location, const Tile &NewTile){
    if(Location==TileLocation) OnTileChangement(NewTile);
}

TileEntity::~TileEntity(){}
