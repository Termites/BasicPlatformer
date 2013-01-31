#include <SFML/Window.hpp>
#include "Player.hpp"
#include "../../../LevelManager/LevelManager.hpp"
#include "../../../ResourceManager/ResourceManager.hpp"

extern const sf::Input *GlobalInput;
extern ResourceManager R;

Player::Player(const vec2f &Location) : Entity(Location){}

void Player::Tick(){
    if(GlobalInput->IsKeyDown(sf::Key::Left) || GlobalInput->IsKeyDown(sf::Key::Right)){
        if(GlobalInput->IsKeyDown(sf::Key::Left)) Velocity.x-=0.5;
        else if(GlobalInput->IsKeyDown(sf::Key::Right)) Velocity.x+=0.5;
    }
    else{
        if(Velocity.x>0) Velocity.x-=0.25;
        if(Velocity.x<0) Velocity.x+=0.25;
    }
    if(GlobalInput->IsKeyDown(sf::Key::Left) && GlobalInput->IsKeyDown(sf::Key::Right)){
        if(Velocity.x>0) Velocity.x-=0.25;
        if(Velocity.x<0) Velocity.x+=0.25;
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
    Entity::WireDraw();
    R.DrawSprite(Spr,Location,0,vec2f(1,1));
}
