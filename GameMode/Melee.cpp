#include "Melee.hpp"

Melee::Melee(Game* game) : GameMode(game), hud(nullptr) {
    sf::Vector2f pos = this->generate_pos();
    tanks["human"] = new Human(textureManager, pos.x, pos.y, "human", NO_TEAM);
    tankToFollow = "human";
    mainPlayer = "human";

    for(uint a(0); a < 9; a++)
    {
        sf::Vector2f pos = this->generate_pos();
        std::string name = "bot_" + Str::convert(a);

        tanks[name] = new IA(textureManager, pos.x, pos.y, name, NO_TEAM, tanks);
    }

    for(auto& i : tanks) scores[i.first] = 0;

    hud = new HUD_Melee(game->window.getSize(), fontManager);
    hud->addMessage("Go ! Good luck !");
}

Melee::~Melee()
{
    delete hud;
}

void Melee::draw() {
    //Display game
    GameMode::draw();

    //Display HUD
    hud->draw(game->window);
    game->window.setView(view);
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

    //Hud
    hud->update();
}

void Melee::handleKills()
{
    while(!kills.empty())
    {
        //Points counting
        scores[kills.top().killer] += 1;

        //Message
        std::string msg = kills.top().victim + " was killed by " + kills.top().killer + " !";
        hud->addMessage(msg);

        kills.pop();

        //Get the 3 best player
        std::pair<std::string, int> bests[3];
        for(unsigned int a(0); a < 3; a++) {
            bests[a] = {"", 0};
        }

        //Get the first
        int best(-1);
        for(auto& player : scores) {
            if(best < 0 || player.second > best) {
                bests[0] = {player.first, player.second};
                best = player.second;
            }
        }
        //Get the second
        for(auto& player : scores) {
            if(player.second > bests[1].second && player.first != bests[0].first) {
                bests[1] = {player.first, player.second};
            }
        }

        //Get the third
        for(auto& player : scores) {
            if(player.second > bests[2].second && player.first != bests[0].first && player.first != bests[1].first) {
                bests[2] = {player.first, player.second};
            }
        }

        hud->setBests(bests);
    }
}
