#include "Player.hpp"
#include "../LevelManager.hpp"
#include "../SoundManager.hpp"
#include <SFML/Window.hpp>

extern const sf::Input * GlobalInput;
extern ResourceManager R;
extern SoundManager SM;
Player::Player(const vec2f & Location) : EntityBase(Location)
{
    CurrentSprite = R.LoadSprite("fario",vec2i(17,17),vec2i(0,0));
    AnimationList = R.LoadAnimationSet("Fario");
    PlayAnimation("idle");
    SpriteOffset=vec2i(8,17);
    JumpSound = R.LoadSound("MarioJump");
    LandSound = R.LoadSound("FarioLandB");
    //BrickDestroyed = R.LoadSound("BrickDestroyed");
    AirControl = 0.4;
    Accel = 0.25;
    Height=1;

}

void Player::HitAbove()
{
    const Tile & B = Level->GetBlockAt(GridLocationExt - vec2i(0,1));
    if (B.BlockID == 15)
    {
        Level->SetBlockAt(GridLocationExt-vec2i(0,1),Tile(0,false));
    }
}

void Player::Tick()
{
    if (GlobalInput->IsKeyDown(sf::Key::Left))
    {
        //Velocity.x = -4;
        Acceleration.x = -Accel;
        if (Physic != PHYS_Landed && fabs(Velocity.x)>=4)
            Acceleration.x*=AirControl;
        Direction=-1;
    }
    else if (GlobalInput->IsKeyDown(sf::Key::Right))
    {
        //Velocity.x = 4;
        Acceleration.x = Accel;
        if (Physic != PHYS_Landed && fabs(Velocity.x)>=4 )
            Acceleration.x*=AirControl;
        Direction=1;
    }
    else
    {
        if (fabs(Velocity.x)>0.5)
        {
            Acceleration.x = -sign(Velocity.x)*.25;

            if (Physic != PHYS_Landed )
                Acceleration.x*=AirControl;

        }
        else
        {
            Velocity.x = 0;
            Acceleration.x=0;
        }
    }


    if (GlobalInput->IsKeyDown(sf::Key::Space) && Physic == PHYS_Landed && !Level->GetBlockAt(GridLocationExt + vec2i(0,-1)).bSolid)
    {
        Physic = PHYS_Jumping;
    	Velocity.y = -8;
        PlayAnimation("jump");
        MaxJumpHeight = Location.y - 60;
        SM.PlaySound(JumpSound);

    }

    if (Physic == PHYS_Jumping && (!GlobalInput->IsKeyDown(sf::Key::Space) || (Location.y+Velocity.y < MaxJumpHeight)))
        Physic = PHYS_Falling;

    if (Physic == PHYS_Landed)
    {
        if (Velocity.x ==0)
            PlayAnimation("idle");
        else
        {
            if (Direction == sign(Velocity.x))
                PlayAnimation("walk");
            else
                PlayAnimation("turn");
        }
    }

    vec2f & C = Level->GetCameraLocation();

    int S = Velocity.x==0 ? Direction : sign(Velocity.x);
    if ( (S<0 && Location.x+Velocity.x < C.x ) ||  (S>0 && Location.x+Velocity.x+16 > C.x + 320))
    {
        Velocity.x = 0;
        Acceleration.x=0;
    }


    C.x = Location.x-160;
    C.y = Location.y-224;

    EntityBase::Tick();

}

 void Player::Land()
{
    SM.PlaySound(LandSound);
}
