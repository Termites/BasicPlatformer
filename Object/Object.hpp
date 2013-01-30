#pragma once
#include "../Math/Math.hpp"

class LevelManager;

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

	protected:
	    LevelManager *Level;
};
