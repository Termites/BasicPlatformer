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
    if(GlobalInput->IsKeyDown(sf::Key::Space) && Velocity.y == 0 && !Jumping){
    	Velocity.y = -8;
        Jumping=true;
    }
    else{
        Jumping=false;
    }
    Entity::Tick();
}
