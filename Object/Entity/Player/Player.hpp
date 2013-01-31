#pragma once
#include "../Entity.hpp"

class Player : public Entity{
    private:

	public:
	    Player(const vec2f &L);
		virtual void Tick();
		virtual void Draw();

	protected:
        int MaxHeight;
};
