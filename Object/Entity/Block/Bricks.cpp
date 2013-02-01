#include "Bricks.hpp"

extern ResourceManager R;

Bricks::Bricks(const vec2i &Location) : Entity(Location){
    this->Location=Location*16;
    Spr=R.LoadSprite("Bricks",vec2i(16,16));
    Anims=R.LoadAnim("Bricks");
    PlayAnim("break");
    Physic=PHYS_Falling;
    Velocity.y=-5;
    Gravity=0.5;
    bEnableLevelCollision=false;
}
