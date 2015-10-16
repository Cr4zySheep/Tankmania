#ifndef MELEE_HPP_INCLUDED
#define MELEE_HPP_INCLUDED

#include "GameMode.hpp"
#include "../HUD/HUD_Melee.hpp"

constexpr int MAX_KILLS = 20;     //Number of kill to do to win
constexpr int MAX_TIME = 10 * 60; //Max game time in seconds

class Melee : public GameMode
{
private:
    sf::String bestPlayers[3];
    HUD_Melee* hud;

    void orderBestPlayers();

    void handleKills();
    virtual bool isFinished();

public:
    Melee(Game* game);
    virtual ~Melee();

    virtual void draw();
    virtual void update(float dt);
};

#endif // MELEE_HPP_INCLUDED
