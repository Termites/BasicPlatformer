#include "TileEntity.hpp"

TileEntity::TileEntity(const vec2i &Location){
    Entity(Location*16);
    TileLocation=Location;
}

void TileEntity::Create(){
    Level->SetBlockAt(TileLocation,Tile(1,false));
}

void TileEntity::TileChanged(const vec2i &Location, const Tile&NewTile){
    if(Location==TileLocation && NewTile.bSolid==false && NewTile.BlockID!=15) OnTileChangement(NewTile);
}

TileEntity::~TileEntity(){}
