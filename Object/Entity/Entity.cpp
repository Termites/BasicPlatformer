#include <GL/GL.h>
#include "../../LevelManager/LevelManager.hpp"
#include "Entity.hpp"

Entity::Entity(){
	Gravity=0.7;
	Layer=0;
	MaxSpeedX=5;
	MaxSpeedY=10;
	Physic=PHYS_Falling;
	Height=1;
	Direction=1;
	CurrentAnim=NULL;
	FrameIndex=0;
}

Entity::Entity(const vec2f &Location){
	this->Location=Location;
	Gravity=0.7;
	Layer=0;
	MaxSpeedX=5;
	MaxSpeedY=10;
	Physic=PHYS_Falling;
	Height=1;
	Direction=1;
	CurrentAnim=NULL;
	FrameIndex=0;
}

void Entity::Create(){}

Entity NextLocation;

void Entity::Tick(){
	Velocity+=Acceleration;
	if(Physic==PHYS_Falling) Velocity.y+=Gravity;
	if(fabs(Velocity.x)>MaxSpeedX) Velocity.x=sign(Velocity.x)*MaxSpeedX;
    if(fabs(Velocity.y)>MaxSpeedY) Velocity.y=sign(Velocity.y)*MaxSpeedY;
    int SignX(0);
    if(Velocity.x!=0) SignX=sign(Velocity.x);
    GridLocation=SnapToGrid(Location)/16;
    if(Physic!=PHYS_Landed){
        if (Velocity.y>0 && Level->GetBlockAt(GridLocation+vec2i(0,1))>0 && Location.y+Velocity.y>=GridLocation.y*16){
            Velocity.y=0;
            Physic=PHYS_Landed;
            Location.y=GridLocation.y*16;
        }
    }
    if(Physic==PHYS_Landed){
        if(Level->GetBlockAt(GridLocation+vec2i(0,1))<=0) Physic=PHYS_Falling;
    }
    if(Physic==PHYS_Jumping){
        if(Velocity.y>0){
            Physic=PHYS_Falling;
            if(Level->GetBlockAt(GridLocation+vec2i(0,1))>0) Velocity.y=0;
        }
        else
        {
            if(Level->GetBlockAt(GridLocation+vec2i(0,-1))>0){
                Velocity.y=0;
                Physic=PHYS_Falling;
            }
        }
    }
    int Block;
    if(Velocity.x!=0){
        int Sign=sign(Velocity.x);
        for (int i=0; i<Height; i++){
			Block=Level->GetBlockAt(GridLocation+vec2i(Sign,-i));
			if(Block>0){
                Velocity.x=0;
                Location.x=(GridLocation.x)*16;
			}
		}
	}
	Block=Level->GetBlockAt(GridLocation);
    if(Block>0){
        Location.y-=16;
        Location.x=(GridLocation.x)*16;
    }
	Location+=Velocity;
}

void Entity::Draw(){
    glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		glVertex3f(Location.x,Location.y,Layer);
		glVertex3f(Location.x+16,Location.y,Layer);
		glVertex3f(Location.x+16,Location.y+16,Layer);
		glVertex3f(Location.x,Location.y+16,Layer);
	glEnd();
}

void Entity::WireDraw(){
    vec2i gLocation=GridLocation*16;
    glEnable(GL_TEXTURE_2D);
	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
        glVertex3f(gLocation.x,gLocation.y,Layer+1);
		glVertex3f(gLocation.x+16,gLocation.y,Layer+1);
		glVertex3f(gLocation.x+16,gLocation.y+16,Layer+1);
		glVertex3f(gLocation.x,gLocation.y+16,Layer+1);
	glEnd();
    glColor3f(1,1,1);
}
