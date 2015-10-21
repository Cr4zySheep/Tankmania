#include "BulletsManager.hpp"

std::vector<Bullet> BulletsManager::bullets = std::vector<Bullet>();

void BulletsManager::addBullet(sf::Texture& texture, float x, float y, float direction, sf::String const shooter, int const team) {
    BulletsManager::bullets.push_back(Bullet(texture, x, y, direction, shooter, team));
}

void BulletsManager::removeBullet(unsigned int const a) {
    BulletsManager::bullets.erase(BulletsManager::bullets.begin() + a);
}

void BulletsManager::eraseAllBullets() {
    std::vector<Bullet> emptyVector;
    BulletsManager::bullets.swap(emptyVector);
}

Bullet& BulletsManager::getBullet(unsigned int const a) {
    return BulletsManager::bullets[a];
}

unsigned int BulletsManager::bulletsCount() {
    return BulletsManager::bullets.size();
}

void BulletsManager::draw(sf::RenderWindow& window) {
    for(auto& bullet : BulletsManager::bullets) bullet.draw(window);
}

void BulletsManager::update(float dt) {
    for(int a(BulletsManager::bulletsCount() - 1); a >= 0 ; a--) {
        Bullet& bullet = BulletsManager::getBullet(a);
        bullet.update(dt);
        if(!bullet.alive()) {
            BulletsManager::removeBullet(a);
        }
    }
}
