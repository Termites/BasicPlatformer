#pragma once
#include "../Player.hpp"

extern ResourceManager R;

class Fario : public Player{
    private:

	public:
        Fario(const vec2f &L) : Player(L){
            Spr=R.LoadSprite("Fario");
        }

	protected:
};
