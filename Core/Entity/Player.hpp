#pragma once

#include "EntityBase.hpp"


class Player : public EntityBase
{
	private:

	public:
		Player(const vec2f&L);

		virtual void Tick();
		//virtual void Draw();

		virtual ~Player() {}
};
