#ifndef MELEE_HPP_INCLUDED
#define MELEE_HPP_INCLUDED

#include "GameMode.hpp"
#include <sstream>

class Melee : public GameMode
{
private:
    std::map<std::string, int> scores;

    void handleKills();

public:
    Melee(Game* game);
    ~Melee();

    virtual void update(float dt);
};

#endif // MELEE_HPP_INCLUDED
