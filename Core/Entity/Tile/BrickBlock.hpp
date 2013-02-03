#pragma once
#include "../TileEntity.hpp"

class BrickChunk : public EntityBase
{
    public:
        BrickChunk(const vec2f&Location,const vec2f&InitVel);
        void Tick();
        void Draw();
};

class BrickBlock : public TileEntity
{
	protected:
		 sf::SoundBuffer *HitSound;
	public:

		BrickBlock(const vec2i&);
		virtual void OnTileChangement(const Tile&New);
};
