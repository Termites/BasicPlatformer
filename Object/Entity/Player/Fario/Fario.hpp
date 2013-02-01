#pragma once
#include "../Player.hpp"

extern ResourceManager R;

class Fario : public Player{
    private:

	public:
        Fario(const vec2f &L) : Player(L){
            Spr=R.LoadSprite("Fario");
            Anims=R.LoadAnim("Animations");
            PlayAnim("idle");
            SpriteOffset=vec2i(8,16);
        }

	protected:
};
