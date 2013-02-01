#pragma once

#include "../Object.hpp"
#include "../Math.hpp"
#include "../Resources/ResourceManager.hpp"

#include<SFML/Audio.hpp>

enum PhysicState
{
    PHYS_None,
    PHYS_Landed,
    PHYS_Jumping,
    PHYS_Falling
};

inline std::string Str(PhysicState S)
{
    if (S==PHYS_Landed)
        return "PHYS_Landed";
    else if (S == PHYS_Jumping)
        return "PHYS_Jumping";
    else if (S == PHYS_Falling)
        return "PHYS_Falling";
    else
        return "PHYS_Unknow";
}

class EntityBase : public Object
{
	protected :
        // Physic :
		vec2f Location; // Position absolue de l'objet
		vec2f Velocity; // Vitesse de l'objet
		vec2f Acceleration; // Acceleration de l'objet
		vec2f MaxSpeed; // Vitesse maximale

		vec2i GridLocation; // Position de l'objet sur la grille (16)
		vec2i GridLocationExt; // Position de l'objet sur la grille(8)

		float Gravity; // Force de la gravité

		int Layer; // Calque de l'objet

		int Height;

		int Direction;

		PhysicState Physic;

		AnimationSet AnimationList;

		Animation * CurrentAnimation;
		std::string CurrentAnimationName;

		Sprite CurrentSprite;
		vec2i SpriteOffset;

		float FrameIndex;



	public:
        EntityBase();
        EntityBase(const vec2f&Location);
		virtual void Create();
		virtual void Tick();
		virtual void Draw();
		virtual ~EntityBase() {}
		virtual void UpdateAnimation();
		virtual void PlayAnimation(const std::string&);

		virtual void Fall() {}
		virtual void Land() {}
		virtual void HitWall() {}
		virtual void HitAbove() {}

};
