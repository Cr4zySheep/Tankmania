#ifndef BULLET_HPP_INCLUDED
#define BULLET_HPP_INCLUDED

#include "Core/Object.hpp"
#include "Core/TextureManager.hpp"

class Bullet : public Object
{
public:
    uint const damage;
    sf::String const shooter;
    int const team;
    sf::Time lifeTime;

    Bullet(TextureManager& textureManager, float x, float y, float direction, sf::String const _owner, int const _team);
    ~Bullet();

    void handleInput();
    void update(float dt);
    void draw(sf::RenderWindow& window);

    bool alive() const;
};

#endif // BULLET_HPP_INCLUDED
