#include "IA_Shoot.hpp"
#include "IA.hpp"

IA_Shoot::IA_Shoot(IA* _ia) :  ia(_ia), target(nullptr)
{

}

void IA_Shoot::update()
{
    if(target == nullptr) return;

    if(target->isDestroyed()) this->stop();
    else {
        ia->align_barrel(target->getPosition());
        if(Point::distance(ia->getPosition(), target->getPosition()) <= (128*6) * (128*6)) ia->fire();
    }
}

void IA_Shoot::shoot(Tank* tank)
{
    target = tank;
}

void IA_Shoot::stop()
{
    target = nullptr;
}

bool IA_Shoot::has_target() const
{
    if(target == nullptr) return false;
    else return true;
}
