#pragma once
#include "../TileEntity.hpp"

class MysteriousBlock : public TileEntity
{
	protected:
		bool Activated;
		bool Animated;
        sf::SoundBuffer HitSound;
	public:
		MysteriousBlock(const vec2i&Loc);

		virtual void OnTileChangement(const Tile&New);

        virtual void Tick();

		virtual ~MysteriousBlock() {}

};
