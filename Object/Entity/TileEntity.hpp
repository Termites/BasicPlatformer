#include "Entity.hpp"
#include "../../LevelManager/LevelManager.hpp"

class TileEntity : public Entity{
    private:

    public:
        TileEntity(const vec2i &Location);
        virtual void OnTileChangement(const Tile &New){}
        virtual void TileChanged(const vec2i &Location, const Tile &NewTile);
        virtual ~TileEntity();
        virtual void Create();

    protected:
        vec2i TileLocation;
};
