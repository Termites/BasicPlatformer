#include "../TileEntity.hpp"

class MystBlock : public Entity {
    private:

    public:
        MystBlock(const vec2f &Location);
        void OnTileChangement(const Tile &New);

    protected:
        bool Activated;
};
