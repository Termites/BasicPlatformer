#include <GL/GL.h>
#include "../../LevelManager/LevelManager.hpp"
#include "Entity.hpp"

Entity::Entity(){
	Gravity=0.7;
	Layer=0;
	MaxSpeed=8;
}

Entity::Entity(const vec2f &Location){
	this->Location=Location;
	Gravity=0.7;
	Layer=0;
	MaxSpeed = 8;
}

void Entity::Create(){}

void Entity::Tick(){
	Velocity+=Acceleration;
	Velocity.y+=Gravity;
	if(fabs(Velocity.x)>MaxSpeed) Velocity.x=sign(Velocity.x)*MaxSpeed;
    if(fabs(Velocity.y) > MaxSpeed) Velocity.y=sign(Velocity.y)*MaxSpeed;
	if (Velocity.y!=0){
		int Sign=sign(Velocity.y);
		int Block=Level->GetBlockAt(GridLocation+vec2i(0,Sign));
		if(Block>0){
			Velocity.y=0;
			Location.y=(GridLocation.y)*16;
		}
	}
    if (Velocity.x!=0){
		int Sign=sign(Velocity.x);
		int Block=Level->GetBlockAt(GridLocation+vec2i(Sign,0));
		if (Block >0){
			Velocity.x=0;
			Location.x=(GridLocation.x)*16;
		}
	}
	Location+=Velocity;
	GridLocation.x=floor(Location.x/16);
	GridLocation.y=floor(Location.y/16);
}

void Entity::Draw(){
	glBegin(GL_QUADS);
		glVertex3f(Location.x,Location.y,Layer);
		glVertex3f(Location.x+16,Location.y,Layer);
		glVertex3f(Location.x+16,Location.y+16,Layer);
		glVertex3f(Location.x,Location.y+16,Layer);
	glEnd();
}

void Entity::WireDraw(){
    vec2i gLocation=GridLocation*16;
	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
        glVertex3f(gLocation.x,gLocation.y,Layer);
		glVertex3f(gLocation.x+16,gLocation.y,Layer);
		glVertex3f(gLocation.x+16,gLocation.y+16,Layer);
		glVertex3f(gLocation.x,gLocation.y+16,Layer);
	glEnd();
    glColor3f(1,1,1);
}
