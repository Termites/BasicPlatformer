#include <SFML/Window.hpp>
#include "Player.hpp"
#include "../LevelManager.hpp"
#include "../SoundManager.hpp"
extern const sf::Input * GlobalInput;
extern ResourceManager R;
extern SoundManager SM;
Player::Player(const vec2f & Location) : EntityBase(Location)
{
    CurrentSprite = R.LoadSprite("Fario",vec2i(17,17),vec2i(0,0));
    AnimationList = R.LoadAnimationSet("Fario");
    PlayAnimation("idle");
    SpriteOffset=vec2i(8,17);
    JumpSound = R.LoadSound("FarioJump");
    LandSound = R.LoadSound("FarioLand");

}

void Player::Tick()
{
    if (GlobalInput->IsKeyDown(sf::Key::Left))
    {
        Velocity.x = -4;
        Direction=-1;
    }
    else if (GlobalInput->IsKeyDown(sf::Key::Right))
    {
        Velocity.x = 4;
        Direction=1;
    }
    else
        Velocity.x = 0;

    if (GlobalInput->IsKeyDown(sf::Key::Space) && Physic == PHYS_Landed)
    {
        Physic = PHYS_Jumping;
    	Velocity.y = -8;
        PlayAnimation("jump");
        MaxJumpHeight = Location.y - 60;
        SM.PlaySound(JumpSound);

    }

    if (Physic == PHYS_Jumping && !GlobalInput->IsKeyDown(sf::Key::Space) || (Location.y+Velocity.y < MaxJumpHeight))
        Physic = PHYS_Falling;

    if (Physic == PHYS_Landed)
    {
        if (Velocity.x ==0)
            PlayAnimation("idle");
        else
            PlayAnimation("walk");
    }

    vec2f & C = Level->GetCameraLocation();
    C.x = Location.x-160;
    C.y = Location.y-224;




    EntityBase::Tick();

}

 void Player::Land()
{
    SM.PlaySound(LandSound);
}
