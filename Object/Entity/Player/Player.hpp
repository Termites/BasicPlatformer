#pragma once
#include "../Entity.hpp"
#include "../../../ResourceManager/ResourceManager.hpp"

extern ResourceManager R;

class Player : public Entity{
    private:

	public:
	    Player(const vec2f &L){
	        Location=L;
            JumpSound=R.LoadSound("MarioJump");
	    }
		virtual void Tick();

	protected:
        int MaxHeight;
        sf::SoundBuffer JumpSound;
};
