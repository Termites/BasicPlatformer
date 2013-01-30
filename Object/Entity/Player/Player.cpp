#include <SFML/Window.hpp>
#include "Player.hpp"

extern const sf::Input *GlobalInput;

Player::Player(const vec2f &Location) : Entity(Location){
    Jumping=false;
}

void Player::Tick(){
    if(GlobalInput->IsKeyDown(sf::Key::Left) || GlobalInput->IsKeyDown(sf::Key::Right)){
        if(GlobalInput->IsKeyDown(sf::Key::Left)) Velocity.x = -4;
        else if(GlobalInput->IsKeyDown(sf::Key::Right)) Velocity.x = 4;
    }
    else Velocity.x=0;
    if(GlobalInput->IsKeyDown(sf::Key::Space) && Physic==PHYS_Landed){
    	Velocity.y = -8;
        Physic=PHYS_Jumping;
    }
    Entity::Tick();
}
