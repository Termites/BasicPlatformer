#include "EntityBase.hpp"
//class LevelManager;
#include "../LevelManager.hpp"

class TileEntity : public EntityBase
{
	protected:
		vec2i TileLocation;

	public:
		TileEntity(const vec2i&Location);


		virtual void Create();

		virtual void OnTileChangement(const Tile&New) {}

        // Lorsque le niveau change un tile :
		virtual void TileChanged(const vec2i&Location,const Tile&NewTile);

		virtual ~TileEntity() {}

};
