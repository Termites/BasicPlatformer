#pragma once
#include "EntityBase.hpp"


class Player : public EntityBase
{
	protected:
        float MaxJumpHeight;

        int CamTimer;
        int CamXOffset;

        sf::SoundBuffer *JumpSound;
        sf::SoundBuffer *LandSound;

        sf::SoundBuffer *BrickDestroyed;
        float AirControl;
        float Accel;

	public:
		Player(const vec2f&L);

		virtual void Tick();
		//virtual void Draw();

		virtual ~Player() {}

		virtual void Land();
		virtual void HitAbove();
};
