#include "Bricks.hpp"

extern ResourceManager R;

Bricks::Bricks(const vec2i &Location, const vec2f &InitVel) : Entity(Location){
    this->Location=Location*16;
    Spr=R.LoadSprite("Bricks",vec2i(16,16));
    Anims=R.LoadAnim("Bricks");
    PlayAnim("break");
    Physic=PHYS_Falling;
    Velocity=InitVel;
    Gravity=0.5;
    bEnableLevelCollision=false;
}
