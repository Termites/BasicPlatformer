#include <iostream>
#define debug(a,b) std::cout << a << " " << b << std::endl
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "Player.hpp"
#include "../../../LevelManager/LevelManager.hpp"
#include "../../../ResourceManager/ResourceManager.hpp"
#include "../../../ResourceManager/SoundManager.hpp"

extern const sf::Input *GlobalInput;
extern ResourceManager R;
extern SoundManager SM;

void Player::Tick(){
    vec2f &C=Level->GetCameraLocation();
    C.x=Location.x-160;
    C.y=Location.y-224;
    if(GlobalInput->IsKeyDown(sf::Key::Left) || GlobalInput->IsKeyDown(sf::Key::Right)){
        if(GlobalInput->IsKeyDown(sf::Key::Left)){
            Velocity.x-=0.5;
            Direction=-1;
        }
        else if(GlobalInput->IsKeyDown(sf::Key::Right)){
            Velocity.x+=0.5;
            Direction=1;
        }
        PlayAnim("walk");
    }
    else{
        if(Velocity.x>0) Velocity.x-=0.3;
        if(Velocity.x<0) Velocity.x+=0.3;
        if(Velocity.x<0.3 && Velocity.x>-0.3){
            Velocity.x=0;
            PlayAnim("idle");
        }
    }
    if(GlobalInput->IsKeyDown(sf::Key::Left) && GlobalInput->IsKeyDown(sf::Key::Right)){
        if(Velocity.x>0) Velocity.x-=0.3;
        if(Velocity.x<0) Velocity.x+=0.3;
        if(Velocity.x<0.3 && Velocity.x>-0.3){
            Velocity.x=0;
            PlayAnim("idle");
        }
    }
    if(GlobalInput->IsKeyDown(sf::Key::Space) && Physic==PHYS_Landed){
        MaxHeight=Location.y-42;
    	Velocity.y=-5;
        Physic=PHYS_Jumping;
        PlayAnim("jump");
        SM.PlaySound(JumpSound,false);
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
    WireDraw();
}
