#include <iostream>
#define debug(a,b) std::cout << a << " " << b << std::endl
#include <SFML/Window.hpp>
#include "Player.hpp"
#include "../../../LevelManager/LevelManager.hpp"
#include "../../../ResourceManager/ResourceManager.hpp"

extern const sf::Input *GlobalInput;
extern ResourceManager R;

Player::Player(const vec2f &Location) : Entity(Location){}

void Player::Tick(){
    if(GlobalInput->IsKeyDown(sf::Key::Left) || GlobalInput->IsKeyDown(sf::Key::Right)){
        if(GlobalInput->IsKeyDown(sf::Key::Left)){
            Velocity.x-=0.5;
            Direction=-1;
        }
        else if(GlobalInput->IsKeyDown(sf::Key::Right)){
            Velocity.x+=0.5;
            Direction=1;
        }
    }
    else{
        if(Velocity.x>0) Velocity.x-=0.3;
        if(Velocity.x<0) Velocity.x+=0.3;
        if(Velocity.x<0.3 && Velocity.x>-0.3) Velocity.x=0;
    }
    if(GlobalInput->IsKeyDown(sf::Key::Left) && GlobalInput->IsKeyDown(sf::Key::Right)){
        if(Velocity.x>0) Velocity.x-=0.3;
        if(Velocity.x<0) Velocity.x+=0.3;
        if(Velocity.x<0.3 && Velocity.x>-0.3) Velocity.x=0;
    }
    if(GlobalInput->IsKeyDown(sf::Key::Space) && Physic==PHYS_Landed){
        MaxHeight=Location.y-42;
    	Velocity.y=-5;
        Physic=PHYS_Jumping;
    }
    if (!GlobalInput->IsKeyDown(sf::Key::Space) || (Physic==PHYS_Jumping && (Location.y<MaxHeight))) Physic=PHYS_Falling;
    if (Velocity.x<0 && GridLocation.x<=0 && Location.x+Velocity.x<=0){
        Velocity.x=0;
        Location.x=GridLocation.x*16;
    }
    if (Velocity.x>0 && GridLocation.x>=Level->GetSizeX()-1 && (Location.x+Velocity.x)/16>=Level->GetSizeX()-1){
        Velocity.x=0;
        Location.x=GridLocation.x*16;
    }
    Entity::Tick();
}

void Player::Draw(){
    std::map<std::string,Anim>::iterator it;
    Entity::WireDraw();
    if(Physic==PHYS_Landed && Velocity.x==0) it=Anims.find("idle");
    if(Physic==PHYS_Landed && Velocity.x!=0) it=Anims.find("walk");
    if(Physic==PHYS_Jumping || Physic==PHYS_Falling) it=Anims.find("jump");
    FrameIndex+=1/(*it).second.FrameRate;
    if(FrameIndex>=(*it).second.FramesCount) FrameIndex=0;
    int Frame=(*it).second.Frames[(int)FrameIndex];
    R.DrawSprite(Spr,Location,Frame,vec2f(Direction,1));
}
