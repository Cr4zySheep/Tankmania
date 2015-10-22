#include "Bullet.hpp"

Bullet::Bullet(sf::Texture& texture, float x, float y, float direction, sf::String const _shooter, int const _team) : damage(20), shooter(_shooter), team(_team), lifeTime(sf::seconds(10))
{
    this->change_movement(direction * -1, 1500);
    sprite.rotate(direction - 90 + 180);

    this->setTexture(texture, 20, 34);
    this->setPosition(x, y);
    collisionData.circle.radius = 5;
}

Bullet::~Bullet()
{

}

void Bullet::handleInput()
{

}

void Bullet::update(float dt)
{
    lifeTime -= sf::seconds(dt);

    this->move(dt);
}

void Bullet::draw(sf::RenderWindow& window)
{
    if(CollisionManager::isVisible(sprite.getGlobalBounds(), window.getView())) window.draw(sprite);
}

const uint Bullet::getDamage() const {
    return damage;
}

const sf::String Bullet::getShooter() const {
    return shooter;
}

const int Bullet::getTeam() const {
    return team;
}

Bullet& Bullet::operator=(const Bullet& bullet) {
    damage = bullet.damage;
    shooter = bullet.shooter;
    team = bullet.team;
    lifeTime = bullet.lifeTime;
    sprite = bullet.sprite;
    width = bullet.width;
    height = bullet.height;
    collision = bullet.collision;
    collisionData = bullet.collisionData;
    velocity = bullet.velocity;
    direction = bullet.direction;
    motion_vector = bullet.motion_vector;
    return *this;
}

bool Bullet::alive() const
{
    if(lifeTime.asSeconds() > 0) return true;
    else return false;
}
