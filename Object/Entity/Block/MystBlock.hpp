#pragma once
#include "../TileEntity.hpp"

class MystBlock : public TileEntity {
    private:

    public:
        MystBlock(const vec2i &Location);
        void OnTileChangement(const Tile &New);
        void OnAnimEnd();
        void Tick();

    protected:
        bool Activated;
};
