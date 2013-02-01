#pragma once
#include "../Object.hpp"
#include "../../ResourceManager/ResourceManager.hpp"

enum PhysicState{
    PHYS_Landed,
    PHYS_Jumping,
    PHYS_Falling,
    PHYS_None
};

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
		virtual void UpdateAnim();
		virtual void PlayAnim(const std::string &S);
		virtual void HitAbove(){}

    protected :
        vec2f Location;
        vec2f Velocity;
        float Acceleration,Deceleration;
        vec2i GridLocation;
        float Gravity;
        float MaxSpeedX;
        float MaxSpeedY;
        int Layer;
        PhysicState Physic;
        int Height;
        Sprite Spr;
        AnimPack Anims;
        Anim *CurrentAnim;
        std::string CurrentAnimName;
        float FrameIndex;
        int Direction;
        vec2i SpriteOffset;
        vec2i GridLocationExt;
};
