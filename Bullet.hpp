#ifndef BULLET_HPP_INCLUDED
#define BULLET_HPP_INCLUDED

#include "Core/Object.hpp"
#include "Core/Loader.hpp"

class Bullet : public Object
{
private:
    uint damage;
    sf::String shooter;
    int team;

public:
    sf::Time lifeTime;

    Bullet(sf::Texture& texture, float x, float y, float direction, sf::String const _owner, int const _team);
    ~Bullet();

    Bullet& operator=(const Bullet& bullet);

    void handleInput();
    void update(float dt);
    void draw(sf::RenderWindow& window);

    const uint getDamage() const;
    const sf::String getShooter() const;
    const int getTeam() const;

    bool alive() const;
};

#endif // BULLET_HPP_INCLUDED
