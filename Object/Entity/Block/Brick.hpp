#pragma once
#include "../TileEntity.hpp"

class Brick : public TileEntity {
    private:

    public:
        Brick(const vec2i &Location);
        void OnTileChangement(const Tile &New);

    protected:
        bool Broken;
};
