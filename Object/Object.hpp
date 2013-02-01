#pragma once
#include "../Math/Math.hpp"

class LevelManager;
struct Tile;

class Object{
	private:

	public:
		virtual void Tick(){}
		virtual void Draw(){}
		virtual void Create(){}
		virtual ~Object(){}
		void SetLevel(LevelManager *L){
            Level=L;
		}
		virtual void TileChanged(const vec2i &Loc,const Tile &T){}

	protected:
	    LevelManager *Level;
};
