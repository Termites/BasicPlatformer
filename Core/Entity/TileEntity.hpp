#include "EntityBase.hpp"
#include "../LevelManager.hpp"

class TileEntity : public EntityBase
{
	protected:
		vec2i TileLocation;

	public:
		TileEntity(const vec2i&Location);

		virtual void OnTileChangement(const Tile&New) {}

		virtual void TileChanged(const vec2i&Location,const Tile&NewTile);

		virtual ~TileEntity();
};
