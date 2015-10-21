#ifndef BULLETSMANAGER_HPP_INCLUDED
#define BULLETSMANAGER_HPP_INCLUDED

#include "Bullet.hpp"
#include <vector>

class BulletsManager {
private:
    static std::vector<Bullet> bullets;

public:
    static void addBullet(sf::Texture& texture, float x, float y, float direction, sf::String const _shooter, int const _team);
    static void removeBullet(unsigned int const a);
    static void eraseAllBullets();
    static Bullet& getBullet(unsigned int const a);
    static unsigned int bulletsCount();
    static void draw(sf::RenderWindow& window);
    static void update(float dt);
};

#endif // BULLETSMANAGER_HPP_INCLUDED
