#ifndef TANK_HPP_INCLUDED
#define TANK_HPP_INCLUDED

#include "BulletsManager.hpp"
#include "HealthBar.hpp"
#include "Core/Label.hpp"
#include "App.hpp"

constexpr float TANK_VELOCITY_MAX(400);
constexpr float TANK_RELOAD_TIME(0.8);

enum {
    NO_TEAM,
    TEAM_1,
    TEAM_2
};

class Tank : public Object
{
protected:
    sf::Sprite barrel;
    float barrel_angle;
    sf::Clock reloading;
    void init_barrel();
    void update_barrel();

    void regulate_velocity();

    App& app;

    HealthBar health;
    bool destroyed;
    bool affected;
    sf::Clock respawn;

    Label labelName;
    void adapt_labelName();

public:
    sf::String const name;
    int const team;

    Tank(App& app, float x, float y, sf::String const _name, int const _team = NO_TEAM);
    virtual ~Tank();

    void handleInput() = 0;
    void update(float dt) = 0;
    void draw(sf::RenderWindow& window);

    void change_direction(float const new_direction);
    void align_barrel(sf::Vector2f point);
    void fire();
    bool damaged(Bullet& bullet);
    void spawn(sf::Vector2f pos);
    bool need_to_spawn();


    const sf::Color getColorName() const;

    bool isDestroyed() const;
};

#endif // TANK_HPP_INCLUDED
