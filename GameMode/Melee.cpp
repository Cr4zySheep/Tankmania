#include "Melee.hpp"

Melee::Melee(Game* game) : GameMode(game) {
    sf::Vector2f pos = this->generate_pos();
    tanks["human"] = new Human(textureManager, pos.x, pos.y, "human", NO_TEAM);
    tankToFollow = "human";
    mainPlayer = "human";

    for(uint a(0); a < 9; a++)
    {
        sf::Vector2f pos = this->generate_pos();
        std::stringstream ss;
        ss << a;
        std::string name = "bot_" + ss.str();

        tanks[name] = new IA(textureManager, pos.x, pos.y, name, NO_TEAM, tanks);
    }

    for(auto& i : tanks) scores[i.first] = 0;
}

Melee::~Melee()
{
    std::cout << scores.size();
}

void Melee::update(float dt)
{
    this->limit_dt(dt);

    for(auto& tank : tanks)
    {
        this->get_bullet(tank.second);
        this->handleCollision(tank.second, dt);

        if(tank.second->need_to_spawn()) tank.second->spawn(this->generate_pos());
        else tank.second->update(dt);
    }

    this->update_bullets(dt);
    this->align_player_barrel();
    this->scrolling();
    this->handleKills();
}

void Melee::draw() {
    GameMode::draw();
}

void Melee::handleKills()
{
    while(!kills.empty())
    {
        //Points counting
        scores[kills.top().killer] += 1;

        //Message
        std::cout << kills.top().victim << " was killed by " << kills.top().killer << " !" << std::endl;

        kills.pop();
    }
}
