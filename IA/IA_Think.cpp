#include "IA_Think.hpp"
#include "IA.hpp"

IA_Think::IA_Think(IA* _ia) : ia(_ia)
{

}

void IA_Think::update()
{
    if(ia->shoot.has_target()) return;
    //If no target
    //Find the closest and kill it !
    std::string best;
    float min(0);
    for(auto& i : ia->tanks) if(i.second->name != ia->name)
    {
        float d = Point::distance(ia->getPosition(), i.second->getPosition());
        if(min == 0 || d < min)
        {
            best = i.first;
            min = d;
        }
    }
    ia->shoot.shoot(ia->tanks[best]);
    ia->follow.follow(ia->tanks[best]);
}
