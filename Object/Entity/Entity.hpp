#pragma once
#include "../Object.hpp"

class Entity : public Object
{
    private:

	public:
        Entity();
        virtual ~Entity(){}
        Entity(const vec2f &Location);
		virtual void Create();
		virtual void Tick();
		virtual void Draw();
		virtual void WireDraw();

    protected :
        vec2f Location;
        vec2f Velocity;
        vec2f Acceleration;
        vec2i GridLocation;
        float Gravity;
        float MaxSpeed;
        int Layer;
};