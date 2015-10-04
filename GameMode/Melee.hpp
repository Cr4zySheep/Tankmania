#ifndef MELEE_HPP_INCLUDED
#define MELEE_HPP_INCLUDED

#include "GameMode.hpp"
#include "../HUD/HUD_Melee.hpp"

class Melee : public GameMode
{
private:
    std::map<std::string, int> scores;
    HUD_Melee* hud;

    void handleKills();

public:
    Melee(Game* game);
    virtual ~Melee();

    virtual void draw();
    virtual void update(float dt);
};

#endif // MELEE_HPP_INCLUDED
