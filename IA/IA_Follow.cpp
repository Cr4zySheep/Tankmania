#include "IA_Follow.hpp"
#include "IA.hpp"

IA_Follow::IA_Follow(IA* _ia) : ia(_ia), target(nullptr)
{

}

void IA_Follow::follow(Tank* tank)
{
    target = tank;
    ia->moving.go_to(Point(target->getPosition()));
    clock.restart();
}

void IA_Follow::update()
{
    if(target == nullptr) return;

    float distance = Point::distance(ia->getPosition(), target->getPosition());
    //Trop loin, on se rapproche
    if(distance > (128*3)*(128*3))
    {
        sf::Time time = clock.getElapsedTime();
        if(time.asSeconds() >= 0.5)
        {
            ia->moving.go_to(Point(target->getPosition()));
            clock.restart();
        }
    }
    //Trop prêt, on s'arrete
    else if(distance < 128*128*4)
    {
        ia->moving.stop();
    }
}

void IA_Follow::stop()
{
    target = nullptr;
    ia->moving.stop();
}

bool IA_Follow::has_target() const
{
    if(target == nullptr) return false;
    else return true;
}
