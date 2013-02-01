#include "../TileEntity.hpp"

class MystBlock : public TileEntity {
    private:

    public:
        MystBlock(const vec2i &Location);
        void OnTileChangement(const Tile &New);

    protected:
        bool Activated;
};
