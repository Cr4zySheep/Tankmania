#include "Tank.hpp"

Tank::Tank(TextureManager& tM, sf::Font& _font, float x, float y, std::string _name, int const _team) : Object(tM.getRef("tankBeige"), x, y, 83, 78), textureManager(tM), bullet(nullptr), health(100), destroyed(false), name(_name), team(_team),
    affected(false), font(_font), labelName(ALIGN_CENTER)
{
    sprite.rotate(90);
    barrel.rotate(90);
    this->init_barrel();
    this->update_barrel();

    sf::Color color;
    if(team == NO_TEAM) {
        color = {rand() % 255, rand() % 255, rand() % 255};
    } else if(team == TEAM_1) {
        color = {0, 0, 255};
    } else if(team == TEAM_2) {
        color = {153, 0, 51};
    }

    labelName.setFont(font);
    labelName.modifyText(this->name, color, 36);
    this->adapt_labelName();

    collisionData.circle.radius = 40;
    collisionData.circle.center = this->getPosition();
}

Tank::~Tank()
{
    delete bullet;
}

void Tank::update(float dt)
{
    health.update({this->getPosition().x, this->getPosition().y + 50});

    this->move(dt);

    update_barrel();
    if(bullet != 0) bullet->update(dt);

    this->adapt_labelName();
}

void Tank::draw(sf::RenderWindow& window)
{
    //HealthBar
    if(!this->isDestroyed()) health.draw(window);

    //Tank
    window.draw(sprite);
    if(bullet != 0) bullet->draw(window);
    window.draw(barrel);

    //Name
    labelName.draw(window);
}

void Tank::init_barrel()
{
    barrel.setOrigin(sf::Vector2f(12, 58));
    barrel.setTexture(textureManager.getRef("barrelBeige"));
    float sx((float)20 / (float)barrel.getTexture()->getSize().x),
          sy((float)58 / (float)barrel.getTexture()->getSize().y);
    barrel.scale(sx, sy);
}

void Tank::update_barrel()
{
    barrel.setPosition(this->left() + this->getWidth() / 2, this->top() + this->getHeight() / 2);
}

bool Tank::need_to_spawn()
{
    if(!this->isDestroyed()) return false;

    sf::Time elapsed = respawn.getElapsedTime();
    if(elapsed.asSeconds() >= 2) return true;
    else return false;

}

void Tank::regulate_velocity()
{
    if(velocity < tank_velocity_max * -1) velocity = tank_velocity_max * -1;
    if(velocity > tank_velocity_max) velocity = tank_velocity_max;
}

void Tank::change_direction(float const new_direction)
{
    float angle = direction - new_direction;
    sprite.rotate(angle);
    direction = new_direction;
}

void Tank::align_barrel(sf::Vector2f point)
{
    if(this->isDestroyed()) return;
    float angle = atan2(point.y - this->getPosition().y, point.x - this->getPosition().x) * 180 / PI;
    barrel.rotate(angle - barrel_angle);
    barrel_angle = angle;
}

void Tank::fire()
{
    sf::Time time = reloading.getElapsedTime();
    if(time.asSeconds() > 2)
    {
        delete bullet;
        bullet = new Bullet(textureManager, this->getPosition().x, this->getPosition().y, barrel_angle, name, team);
        reloading.restart();
    }
}

Bullet* Tank::getBullet()
{
    Bullet* bullet = this->bullet;
    this->bullet = nullptr;
    return bullet;
}

bool Tank::isDestroyed() const
{
    return destroyed;
}

bool Tank::damaged(Bullet* bullet)
{
    health.remove(bullet->damage);
    affected = true;

    //Died ?
    if(health.get_health() == 0 && destroyed == false)
    {
        destroyed = true;
        respawn.restart();
    }

    return this->isDestroyed();
}

void Tank::spawn(sf::Vector2f pos)
{
    destroyed = false;
    sprite.setPosition(pos);
    barrel.setPosition(pos);
    velocity = 0;
    health.set_health(health.get_max());
}

void Tank::adapt_labelName() {
    labelName.setPosition(this->getPosition().x, this->getPosition().y - 100);
}

const sf::Color Tank::getColorName() const {
    return labelName.getColor();
}
