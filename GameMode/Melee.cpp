#include "Melee.hpp"

Melee::Melee(Game* game) : GameMode(game), hud(nullptr) {
    sf::Vector2f pos = this->generate_pos();
    tanks["human"] = new Human(textureManager, pos.x, pos.y, "human", NO_TEAM);
    tankToFollow = "human";
    mainPlayer = "human";

    for(uint a(0); a <3; a++) {
        bestPlayers[a] = "";
    }

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

    if(this->isFinished()) {
        this->finish();
    }

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

        //Update ranking of HUD
        this->orderBestPlayers();
        std::pair<std::string, int> bests[3];
        bests[0] = {bestPlayers[0], scores[bestPlayers[0]]};
        bests[1] = {bestPlayers[1], scores[bestPlayers[1]]};
        bests[2] = {bestPlayers[2], scores[bestPlayers[2]]};
        hud->setBests(bests);
    }
}

void Melee::orderBestPlayers() {
    int best(-1);
    for(auto& player : scores) {
        if(best < 0 || player.second > best) {                                                                           //First
            bestPlayers[0] = player.first;
            best = player.second;
        } else if(player.second > scores[bestPlayers[1]] && player.first != bestPlayers[0]) {                                   //Second
            bestPlayers[1] = player.first;
        } else if(player.second > scores[bestPlayers[2]] && player.first != bestPlayers[0] && player.first != bestPlayers[1]) { //Third
            bestPlayers[2] = player.first;
        }
    }
}

bool Melee::isFinished() {
    if(!bestPlayers[0].empty() && scores[bestPlayers[0]] >= MAX_KILLS) {
        return true;
    } else if(hud->getTime().asSeconds() >= MAX_TIME) {
        return true;
    }

    return false;
}

void Melee::finish() {
    hud->addMessage("Game finished !");

}
