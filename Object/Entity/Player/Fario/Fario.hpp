#pragma once
#include "../Player.hpp"

extern ResourceManager R;

class Fario : public Player{
    private:

	public:
        Fario(const vec2i &L) : Player(L){
            Spr=R.LoadSprite("Fario",vec2i(17,17));
            Anims=R.LoadAnim("Fario");
            PlayAnim("idle");
            SpriteOffset=vec2i(8,16);
            Acceleration=0.5;
            Deceleration=0.3;
        }

	protected:
};
