#include "TileEntity.hpp"

TileEntity::TileEntity(const vec2i&Location)
{
	EntityBase(Location*16);
	TileLocation = Location;
	Level->SetBlockAt(Location,Tile(15,true));
}


void TileEntity::TileChanged(const vec2i&Location,const Tile&NewTile)
{
	if (Location == TileLocation && NewTile.bSolid==false)
		OnTileChangement(NewTile);
}

TileEntity::~TileEntity(){}
