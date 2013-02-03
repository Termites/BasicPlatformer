#include "BrickBlock.hpp"
#include "../../SoundManager.hpp"
//#include ".ResourceManager.hpp"
extern ResourceManager R;
extern SoundManager SM;

BrickBlock::BrickBlock(const vec2i&L) : TileEntity(L)
{
	CurrentSprite = R.LoadSprite("Brick",vec2i(16,16),vec2i(0,0));
	AnimationList = R.LoadAnimationSet("default");
	PlayAnimation("default");
	HitSound = R.LoadSound("BrickDestroyed");
}

void BrickBlock::OnTileChangement(const Tile&New)
{
    Level->RegisterObject(new BrickChunk(Location+vec2f(0,0),vec2f(-2,-6)));
    Level->RegisterObject(new BrickChunk(Location+vec2f(16,0),vec2f(2,-6)));
    Level->RegisterObject(new BrickChunk(Location+vec2f(16,16),vec2f(2,-6)));
    Level->RegisterObject(new BrickChunk(Location+vec2f(0,16),vec2f(2,-6)));
    SM.PlaySound(HitSound);
    Destroy();

}

BrickChunk::BrickChunk(const vec2f&Location,const vec2f&InitVel) : EntityBase(Location)
{
	Velocity = InitVel;
	Physic = PHYS_Falling;
	CurrentSprite = R.LoadSprite("BrickChunk",vec2i(7,7),vec2i(0,0));
	CurrentAnimation=NULL;
	bEnableLevelCollision=false;
}

void BrickChunk::Tick()
{
	EntityBase::Tick();
	if (Location.y >= Level->GetCameraLocation().y + 280)
		Destroy();
}
void BrickChunk::Draw()
{
	R.DrawSprite(CurrentSprite,0,Location - Level->GetCameraLocation(),90,vec2i(1,1));
}
