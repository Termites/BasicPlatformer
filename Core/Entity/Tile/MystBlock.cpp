#include "MystBlock.hpp"
#include "../../SoundManager.hpp"
extern ResourceManager *R;
extern SoundManager SM;
MysteriousBlock::MysteriousBlock(const vec2i&Loc) : TileEntity(Loc)
{
	Activated=false;
	Animated=false;
	AnimationList = R->LoadAnimationSet("MystBlock");
	CurrentSprite = R->LoadSprite("MysteriousBlock",vec2i(16,16),vec2i(0,0));
	PlayAnimation("idle");
	HitSound = R->LoadSound("Bump");
}

void MysteriousBlock::OnTileChangement(const Tile&New)
{
    SM.PlaySound(*HitSound);
	Level->SetBlockAt(TileLocation,Tile(0,true));
	PlayAnimation("deactivated");
	Physic = PHYS_Falling;
	Velocity.y=-3;
	Activated=true;
}

void MysteriousBlock::Tick()
{
    if (Activated && Velocity.y>0 && Location.y + Velocity.y>=TileLocation.y*16)
    {
        Physic = PHYS_None;
        Location.y = TileLocation.y*16;
        Velocity.y=0;
        //PlayAnimation("deactivated");
    }

    TileEntity::Tick();
}
