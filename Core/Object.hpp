#pragma once

#include "Math.hpp"
// Ici on défini le prototype de LevelManager,
// mais pas ce qu'il contient.
class LevelManager;

struct Tile;

class Object
{
	protected:
			LevelManager * Level;
	public:
		virtual void Create() {}
		virtual void Tick() {}
		virtual void Draw() {}
		virtual ~Object() {}

		void SetLevel(LevelManager * L)
		{
			Level = L;
		}

		virtual void TileChanged(const vec2i&Loc,const Tile&T) {}
};
