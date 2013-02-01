#include "TileEntity.hpp"
#include "../LevelManager.hpp"
#include<iostream>
TileEntity::TileEntity(const vec2i&Location) : EntityBase(vec2i())
{

	TileLocation = Location;
    this->Location = TileLocation*16;
    this->GridLocation = Location;
    this->GridLocationExt = Location;

    Physic = PHYS_None;
}

void TileEntity::Create()
{
    Level->SetBlockAt(TileLocation,Tile(15,true));
}

void TileEntity::TileChanged(const vec2i&Location,const Tile&NewTile)
{
	if (Location == TileLocation && NewTile.bSolid==false && NewTile.BlockID!=15)
		OnTileChangement(NewTile);
}


