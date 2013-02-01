#include "MystBlock.hpp"
#include <iostream>

MystBlock::MystBlock(const vec2f &Location){
    Tile T;
    T.BlockID=8;
    T.bSolid=true;
    TileEntity TE(Location);
}

void MystBlock::OnTileChangement(const Tile &New){
    Level->SetBlockAt(Location,New);
}
