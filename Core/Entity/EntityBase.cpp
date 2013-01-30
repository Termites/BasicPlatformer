#include "EntityBase.hpp"
#include "../LevelManager.hpp"
#include <GL/GL.h>

EntityBase::EntityBase()
{
	Gravity=0.7;
	Layer=0;
	MaxSpeed = 8;
	Physic = PHYS_Falling;
}

EntityBase::EntityBase(const vec2f&Location)
{
	this->Location = Location;
	Gravity=0.7;
	Layer=0;
	MaxSpeed = 8;
	Physic = PHYS_Falling;
}


void EntityBase::Create()
{}

void EntityBase::Tick()
{

	Velocity+=Acceleration;

	if (Physic != PHYS_Landed)
        Velocity.y+=Gravity;

    GridLocation = SnapToGrid(Location)/16;

	if (fabs(Velocity.x ) > MaxSpeed)
		Velocity.x = sign(Velocity.x) * MaxSpeed;

	if (fabs(Velocity.y) > MaxSpeed)
		Velocity.y = sign(Velocity.y) * MaxSpeed;


    if (Physic != PHYS_Landed)
    {

        if (Velocity.y> 0 && Level->GetBlockAt(GridLocation+vec2i(0,1)) > 0 && Location.y + Velocity.y >= GridLocation.y*16)
        {
            Velocity.y= 0;
            Physic = PHYS_Landed;
            Location.y = GridLocation.y * 16;
        }
    }

    if (Physic == PHYS_Landed)
    {
        if (Level->GetBlockAt(GridLocation+vec2i(0,1))<=0)
        {
            Physic = PHYS_Falling;
        }
    }

    if (Physic == PHYS_Jumping)
    {

        if (Velocity.y >0 )
            Physic = PHYS_Falling;
        else
        {
            if (Level->GetBlockAt(GridLocation+vec2i(0,-1))>0)
                {
                    Velocity.y = 0;
                    Physic = PHYS_Falling;
                }
        }

    }

    if (Velocity.x !=0 )
	{
		int Sign = sign(Velocity.x);
		int Block = Level->GetBlockAt(GridLocation + vec2i(Sign,0));
		if (Block >0)
		{
			Velocity.x = 0;
			//Location.x = (GridLocation.x)*16;
		}
	}

	Location+=Velocity;

}

void EntityBase::Draw()
{
	// Juste histoire d'afficher un carré bidon :
	glBegin(GL_QUADS);
		glVertex3f(Location.x,Location.y,Layer);
		glVertex3f(Location.x+16,Location.y,Layer);
		glVertex3f(Location.x+16,Location.y+16,Layer);
		glVertex3f(Location.x,Location.y+16,Layer);
	glEnd();

	vec2i gLocation = GridLocation * 16;
	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
        glVertex3f(gLocation.x,gLocation.y,Layer);
		glVertex3f(gLocation.x+16,gLocation.y,Layer);
		glVertex3f(gLocation.x+16,gLocation.y+16,Layer);
		glVertex3f(gLocation.x,gLocation.y+16,Layer);
	glEnd();

	glColor3f(1,1,1);
}
