#ifndef IA_FOLLOW_HPP_INCLUDED
#define IA_FOLLOW_HPP_INCLUDED

#include "../Tank.hpp"

class IA;

class IA_Follow
{
private:
    IA* ia;
    Tank* target;
    sf::Clock clock;

public:
    IA_Follow(IA* _ia);

    void stop();
    void update();
    void follow(Tank* tank);
    bool has_target() const;
};

#endif // IA_FOLLOW_HPP_INCLUDED
