#pragma once
#include "../Object.hpp"
#include "../Math.hpp"

enum PhysicState
{
    PHYS_Landed,
    PHYS_Jumping,
    PHYS_Falling
};

class EntityBase : public Object
{
	protected :
        // Physic :
		vec2f Location; // Position absolue de l'objet
		vec2f Velocity; // Vitesse de l'objet
		vec2f Acceleration; // Acceleration de l'objet
		float MaxSpeed; // Vitesse maximale

		vec2i GridLocation; // Position de l'objet sur la grille

		float Gravity; // Force de la gravité

		int Layer; // Calque de l'objet

		PhysicState Physic;



	public:
        EntityBase();
        EntityBase(const vec2f&Location);
		virtual void Create();
		virtual void Tick();
		virtual void Draw();
		virtual ~EntityBase() {}

};
