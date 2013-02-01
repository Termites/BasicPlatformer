#include "MystBlock.hpp"

extern ResourceManager R;

MysteriousBlock::MysteriousBlock(const vec2i&Loc) : TileEntity(Loc)
{
	Activated=false;
	Animated=false;
	AnimationList = R.LoadAnimationSet("MystBlock");
	CurrentSprite = R.LoadSprite("MysteriousBlock",vec2i(16,16),vec2i(0,0));
	PlayAnimation("idle");
}

void MysteriousBlock::OnTileChangement(const Tile&New)
{
	//if (Activated==false)
	PlayAnimation("activated");
}

