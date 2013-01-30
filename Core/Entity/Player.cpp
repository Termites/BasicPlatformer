#include <SFML/Window.hpp>
#include "Player.hpp"
extern const sf::Input * GlobalInput;
Player::Player(const vec2f & Location) : EntityBase(Location)
{}

void Player::Tick()
{
    if (GlobalInput->IsKeyDown(sf::Key::Left))
        Velocity.x = -4;
    else if (GlobalInput->IsKeyDown(sf::Key::Right))
        Velocity.x = 4;
    else
        Velocity.x = 0;

    if (GlobalInput->IsKeyDown(sf::Key::Space) && Physic == PHYS_Landed)
    {
        Physic = PHYS_Jumping;
    	Velocity.y = -12;
    }

    EntityBase::Tick();
}
