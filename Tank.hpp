#ifndef TANK_HPP_INCLUDED
#define TANK_HPP_INCLUDED

#include "Bullet.hpp"
#include "HealthBar.hpp"
#include "Core/Label.hpp"

constexpr float tank_velocity_max(400);
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
    Bullet* bullet;
    sf::Clock reloading;
    void init_barrel();
    void update_barrel();

    void regulate_velocity();

    TextureManager& textureManager;
    HealthBar health;
    bool destroyed;
    bool affected;
    sf::Clock respawn;

    sf::Font& font;
    Label labelName;
    void adapt_labelName();

public:
    sf::String const name;
    int const team;

    Tank(TextureManager& tM, sf::Font& _font, float x, float y, sf::String const _name, int const _team = NO_TEAM);
    virtual ~Tank();

    void handleInput() = 0;
    void update(float dt) = 0;
    void draw(sf::RenderWindow& window);

    void change_direction(float const new_direction);
    void align_barrel(sf::Vector2f point);
    void fire();
    bool damaged(Bullet* bullet);
    void spawn(sf::Vector2f pos);
    bool need_to_spawn();


    const sf::Color getColorName() const;

    bool isDestroyed() const;
    Bullet* getBullet();
};

#endif // TANK_HPP_INCLUDED
