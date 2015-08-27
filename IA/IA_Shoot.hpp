#ifndef IA_SHOOT_HPP_INCLUDED
#define IA_SHOOT_HPP_INCLUDED

#include "../Tank.hpp"

class IA;

class IA_Shoot
{
private:
    IA* ia;
    Tank* target;

public:
    IA_Shoot(IA* _ia);

    void update();
    void shoot(Tank* tank);
    bool has_target() const;
    void stop();

};

#endif // IA_SHOOT_HPP_INCLUDED
