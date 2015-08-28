#ifndef IA_THINK_HPP_INCLUDED
#define IA_THINK_HPP_INCLUDED

#include "../Tank.hpp"

class IA;

class IA_Think
{
private:
    IA* ia;

public:
    IA_Think(IA* ia);

    void update();
};

#endif // IA_THINK_HPP_INCLUDED
