#include "EntityBase.hpp"

#include "../LevelManager.hpp"

#include<iostream>
#define debug(a) std::cout<<a<<std::endl

extern ResourceManager * R;
EntityBase::EntityBase(): Object()
{
	Gravity=0.7;
	Layer=0;
	MaxSpeed = vec2f(8,8);
	Physic = PHYS_Falling;
	Height=1;
	CurrentAnimation=NULL;
	FrameIndex=0;
	Direction=1;
	bEnableLevelCollision=true;
}

EntityBase::EntityBase(const vec2f&Location) : Object()
{
	this->Location = Location;
	Gravity=0.7;
	Layer=0;
	MaxSpeed = vec2f(8,8);
	Physic = PHYS_Falling;
	Height=1;
	CurrentAnimation=NULL;
	FrameIndex=0;
	Direction=1;
	bEnableLevelCollision=true;
}


void EntityBase::Create()
{}

void EntityBase::Tick()
{
    Velocity+=Acceleration;

    if (Physic == PHYS_Falling)
        Velocity.y+=Gravity;


    if (fabs(Velocity.x)>MaxSpeed.x)
        Velocity.x = sign(Velocity.x) * MaxSpeed.x;

    if (fabs(Velocity.y)>MaxSpeed.y)
        Velocity.y = sign(Velocity.y) * MaxSpeed.y;

	GridLocation = Location+Velocity;
	GridLocation/=16;
	GridLocationExt = SnapToGrid(Location + Velocity);
	GridLocationExt.x = GridLocation.x;
	GridLocationExt.y--;

	if (bEnableLevelCollision && Physic != PHYS_Landed && Velocity.y >= 0)
	{
		if (Level->GetBlockAt(GridLocation).bSolid  && Location.y + Velocity.y >= GridLocation.y * 16 )
		{
			Velocity.y = 0;
			Location.y = GridLocation.y*16;
			Physic = PHYS_Landed;
			Land();
		}
	}

	if (bEnableLevelCollision && Physic != PHYS_Landed && Velocity.y<0)
	{
	    if (Level->GetBlockAt(GridLocation + vec2i(0,-1)).bSolid)
	    {
	        Physic = PHYS_Falling;
	        Velocity.y=0;
	        HitAbove();

	    }
	}

	if (bEnableLevelCollision && Physic == PHYS_Landed && (!Level->GetBlockAt(GridLocation).bSolid) && Location.x>GridLocation.x*16 && Location.x<GridLocation.x*16+16)
	{
	    Physic = PHYS_Falling;
	    Fall();
	}

	if (bEnableLevelCollision && Velocity.x != 0)
	{
		int S = Velocity.x<0 ? -1 : 1;

		for (int i=0;i<Height;i++)
		{
			if (Level->GetBlockAt(GridLocationExt + vec2i(S,-i)).bSolid)
			{
			    if ( (S>=0 && Location.x + Velocity.x >=GridLocationExt.x*16+8) ||
                     (S<0 && Location.x + Velocity.x <= GridLocationExt.x*16 +8) )
                {
                    Velocity.x=0;
                    Location.x = GridLocationExt.x*16+8;
                    HitWall();
                    break;
                }
			}
		}
	}


	Location+=Velocity;
	UpdateAnimation();

}

void EntityBase::UpdateAnimation()
{
    if (CurrentAnimation!=NULL)
    {
            FrameIndex+=CurrentAnimation->Ratescale;
            if (int(FrameIndex) >= CurrentAnimation->FramesCount)
            {
                AnimationEnded();
                FrameIndex = 0;

            }
    }
}
void EntityBase::PlayAnimation(const std::string&Anim)
{
    if (Anim == CurrentAnimationName)
        return;

    CurrentAnimationName = Anim;

    AnimationSet::iterator it = AnimationList.find(Anim);

    if (it != AnimationList.end())
    {
        Animation & A = it->second;

        CurrentAnimation = &A;
        FrameIndex=0;

    }
    else
        CurrentAnimation = NULL;
}

void EntityBase::Draw()
{
    if (CurrentAnimation!=NULL)
    {
        int i =FrameIndex;
        R->DrawSprite(CurrentSprite,CurrentAnimation->FrameKeys[i],Location - vec2f(SpriteOffset) - Level->GetCameraLocation(),Layer,vec2f(Direction,1));
    }

    /*vec2i gLocation = GridLocation * 16 - vec2i(Level->GetCameraLocation());
	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
        glVertex3f(gLocation.x,gLocation.y,Layer+1);
		glVertex3f(gLocation.x+16,gLocation.y,Layer+1);
		glVertex3f(gLocation.x+16,gLocation.y+16,Layer+1);
		glVertex3f(gLocation.x,gLocation.y+16,Layer+1);
	glEnd();

	gLocation = GridLocationExt * 16 - vec2i(Level->GetCameraLocation());

    glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
        glVertex3f(gLocation.x,gLocation.y,Layer+1);
		glVertex3f(gLocation.x+16,gLocation.y,Layer+1);
		glVertex3f(gLocation.x+16,gLocation.y+16,Layer+1);
		glVertex3f(gLocation.x,gLocation.y+16,Layer+1);
	glEnd();*/

	/*glBegin(GL_LINES);
	glVertex3f(Location.x-8,Location.y,2);
	glVertex3f(Location.x+8,Location.y,2);
	glVertex3f(Location.x,Location.y-8,2);
	glVertex3f(Location.x,Location.y+8,2);
	glEnd();*/

	glColor3f(1,1,1);
}
