#include "IA.hpp"

IA::IA(TextureManager &textureManager, float x, float y, std::string const name, std::map<std::string, Tank*>& _tanks) : Tank(textureManager, x, y, name), follow(this), shoot(this), tanks(_tanks)
{

}

IA::~IA()
{

}

void IA::handleInput()
{
    if(!follow.has_target()) follow.follow(tanks["human"]);
    if(!shoot.has_target()) shoot.shoot(tanks["human"]);

    follow.update();
    moving.update(this);
    shoot.update();

    this->regulate_velocity();
    this->calculate_MotionVector();
}

void IA::update(float dt)
{
    this->move(dt);

    update_barrel();
    if(bullet != 0) bullet->update(dt);
}
