#ifndef BULLETSMANAGER_HPP_INCLUDED
#define BULLETSMANAGER_HPP_INCLUDED

#include "Bullet.hpp"
#include <vector>

class BulletsManager {
private:
    std::vector<Bullet> bullets;

public:
    void addBullet(sf::Texture& texture, float x, float y, float direction, sf::String const _shooter, int const _team);
    void removeBullet(unsigned int const a);
    void eraseAllBullets();
    Bullet& getBullet(unsigned int const a);
    unsigned int bulletsCount();
    void draw(sf::RenderWindow& window);
    void update(float dt);
};

#endif // BULLETSMANAGER_HPP_INCLUDED
