#include <GL/GL.h>
#include "../../LevelManager/LevelManager.hpp"
#include "../../ResourceManager/SoundManager.hpp"
#include "Entity.hpp"

extern ResourceManager R;
extern SoundManager SM;

Entity::Entity(){
	Gravity=0.7;
	Layer=0;
	MaxSpeedX=5;
	MaxSpeedY=10;
	Physic=PHYS_Falling;
	Height=1;
	Direction=1;
	FrameIndex=0;
	CurrentAnim=NULL;
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
	FrameIndex=0;
	CurrentAnim=NULL;
}

void Entity::Create(){}

void Entity::Tick(){
    if(Physic==PHYS_Falling) Velocity.y+=Gravity;
    if(fabs(Velocity.x)>MaxSpeedX) Velocity.x=sign(Velocity.x)*MaxSpeedX;
    if(fabs(Velocity.y)>MaxSpeedY) Velocity.y=sign(Velocity.y)*MaxSpeedY;
	GridLocation=Location+Velocity;
	GridLocation/=16;
	GridLocationExt=SnapToGrid(Location + Velocity);
	GridLocationExt.x=GridLocation.x;
	GridLocationExt.y--;
	if(Physic!=PHYS_Landed && Velocity.y>=0){
		if(Level->GetBlockAt(GridLocation).bSolid  && Location.y+Velocity.y>=GridLocation.y*16 ){
			Velocity.y=0;
			Location.y=GridLocation.y*16;
			Physic=PHYS_Landed;
		}
	}
	if(Physic!=PHYS_Landed && Velocity.y<0){
	    if(Level->GetBlockAt(GridLocation+vec2i(0,-1)).bSolid){
            HitAbove();
	        Physic=PHYS_Falling;
	        Velocity.y=0;
	    }
	}
	if(Physic==PHYS_Landed && (!Level->GetBlockAt(GridLocation).bSolid) && Location.x>GridLocation.x*16 && Location.x<GridLocation.x*16+16) Physic=PHYS_Falling;
	if(Velocity.x!=0){
		int S=Velocity.x<0?-1:1;
		for(int i=0; i<Height; i++){
			if(Level->GetBlockAt(GridLocationExt+vec2i(S,-i)).bSolid){
			    if((S>=0 && Location.x+Velocity.x>=GridLocationExt.x*16+8) || (S<0 && Location.x+Velocity.x<=GridLocationExt.x*16+8)){
                    Velocity.x=0;
                    Location.x=GridLocationExt.x*16+8;
                }
			}
		}
	}
	Location+=Velocity;
	UpdateAnim();
}

void Entity::Draw(){
    if (CurrentAnim!=NULL){
        int i=FrameIndex;
        R.DrawSprite(Spr,Location-vec2f(SpriteOffset)-Level->GetCameraLocation(),CurrentAnim->Frames[i],vec2f(Direction,1));
    }
}

void Entity::WireDraw(){
    vec2i gLocation=GridLocation*16-vec2i(Level->GetCameraLocation());
    glEnable(GL_TEXTURE_2D);
	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
        glVertex3f(gLocation.x,gLocation.y,Layer+1);
		glVertex3f(gLocation.x+16,gLocation.y,Layer+1);
		glVertex3f(gLocation.x+16,gLocation.y+16,Layer+1);
		glVertex3f(gLocation.x,gLocation.y+16,Layer+1);
	glEnd();
    gLocation=GridLocationExt*16-vec2i(Level->GetCameraLocation());
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
        glVertex3f(gLocation.x,gLocation.y,Layer+1);
        glVertex3f(gLocation.x+16,gLocation.y,Layer+1);
        glVertex3f(gLocation.x+16,gLocation.y+16,Layer+1);
        glVertex3f(gLocation.x,gLocation.y+16,Layer+1);
    glEnd();
    glColor3f(1,1,1);
}

void Entity::UpdateAnim(){
    if(CurrentAnim!=NULL){
        FrameIndex+=CurrentAnim->FrameRate;
        if(int(FrameIndex)>=CurrentAnim->FramesCount) FrameIndex=0;
    }
}

void Entity::PlayAnim(const std::string &AnimName){
    if(AnimName==CurrentAnimName) return;
    CurrentAnimName=AnimName;
    std::map<std::string,Anim>::iterator it(Anims.find(AnimName));
    if(it!=Anims.end()){
        Anim &A=it->second;
        CurrentAnim=&A;
        FrameIndex=0;
    }
    else CurrentAnim=NULL;
}
