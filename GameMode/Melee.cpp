#include "Melee.hpp"

Melee::Melee(Game* game) : GameMode(game), hud(nullptr) {
    sf::Vector2f pos = this->generate_pos();
    sf::Font& font = fontManager.getRef("thickhead");

    tanks["human"] = new Human(textureManager, font, pos.x, pos.y, "human", NO_TEAM);
    tankToFollow = "human";
    mainPlayer = "human";

    for(uint a(0); a <3; a++) {
        bestPlayers[a] = "";
    }

    for(uint a(10); a < 19; a++)
    {
        sf::Vector2f pos = this->generate_pos();
        std::string name = "bot_" + Str::convert(a);

        tanks[name] = new IA(textureManager, font, pos.x, pos.y, name, NO_TEAM, tanks);
    }

    for(auto& i : tanks) scores[i.first] = 0;
    scores[""] = 0;

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
        std::pair<std::string, sf::Color> names[2];
        names[0] = {kills.top().victim, tanks[kills.top().victim]->getColorName()};
        names[1] = {kills.top().killer, tanks[kills.top().killer]->getColorName()};
        hud->addMessage(" was killed by ", names);

        kills.pop();

        //Update ranking of HUD
        this->orderBestPlayers();
        std::pair<std::pair<std::string, sf::Color>, int> bests[3];
        for(uint a(0); a < 3; a++) {
            sf::Color color = (!bestPlayers[a].empty()) ? tanks[bestPlayers[a]]->getColorName() : sf::Color::Black;
            bests[a] = {{bestPlayers[a], color}, scores[bestPlayers[a]]};
        }
        hud->setBests(bests);
    }
}

void Melee::orderBestPlayers() {
    bool changed(true);
    while(changed) {
        changed = false;
        for(auto& player : scores) {
            std::string const& name = player.first;
            int const& score = player.second;

            if(name != bestPlayers[0] && score > scores[bestPlayers[0]]) {
                bestPlayers[0] = name;
                bestPlayers[1] = "";
                bestPlayers[2] = "";
                changed = true;
                break;
            } else if(name != bestPlayers[0] && name != bestPlayers[1] && score > scores[bestPlayers[1]]) {
                bestPlayers[1] = name;
                bestPlayers[2] = "";
                changed = true;
                break;
            } else if(name != bestPlayers[0] && name != bestPlayers[1] && name != bestPlayers[2] && score > scores[bestPlayers[2]]) {
                bestPlayers[2] = name;
            }
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
