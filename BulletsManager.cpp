#include "BulletsManager.hpp"

void BulletsManager::addBullet(sf::Texture& texture, float x, float y, float direction, sf::String const shooter, int const team) {
    bullets.push_back(Bullet(texture, x, y, direction, shooter, team));
}

void BulletsManager::removeBullet(unsigned int const a) {
    bullets.erase(BulletsManager::bullets.begin() + a);
}

void BulletsManager::eraseAllBullets() {
    std::vector<Bullet> emptyVector;
    bullets.swap(emptyVector);
}

Bullet& BulletsManager::getBullet(unsigned int const a) {
    return bullets[a];
}

unsigned int BulletsManager::bulletsCount() {
    return bullets.size();
}

void BulletsManager::draw(sf::RenderWindow& window) {
    for(auto& bullet : bullets) bullet.draw(window);
}

void BulletsManager::update(float dt) {
    for(int a(bulletsCount() - 1); a >= 0 ; a--) {
        Bullet& bullet = getBullet(a);
        bullet.update(dt);
        if(!bullet.alive()) {
            removeBullet(a);
        }
    }
}
