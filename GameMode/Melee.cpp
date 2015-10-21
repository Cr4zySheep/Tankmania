#include "Melee.hpp"

Melee::Melee(Game* game) : GameMode(game), hud(nullptr) {
    sf::Vector2f pos = this->generate_pos();
    sf::Font& font = fontManager.getRef("thickhead");

    tanks["You"] = new Human(textureManager, font, pos.x, pos.y, "You", NO_TEAM);
    tankToFollow = "You";
    mainPlayer = "You";

    for(uint a(0); a <3; a++) {
        bestPlayers[a] = "";
    }

    for(uint a(0); a < 9; a++)
    {
        sf::Vector2f pos = this->generate_pos();
        sf::String name = "bot_" + Str::convert(a);

        tanks[name] = new IA(textureManager, font, pos.x, pos.y, name, NO_TEAM, tanks);
    }

    for(auto& i : tanks) {
        scores[i.first]["kills"] = 0;
        scores[i.first]["deaths"] = 0;
    }
    scores[""]["kills"] = 0;

    hud = new HUD_Melee(game->window.getSize(), fontManager);
    hud->addMessage("Try to kill 15 people ! Good luck !");
    hud->addMessage("Press Esc to quit or space to leave the game");
    hud->addMessage("For any feedback, contact me at mura.loic0@gmail.com");
    hud->addMessage("Don't forget to check on itch.io for any new release");
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
    this->align_player_barrel();
    this->scrolling();
    if(!this->updateWaitedTime(dt)) return;

    this->limit_dt(dt);

    for(auto& tank : tanks)
    {
        this->handleCollision(tank.second, dt);

        if(tank.second->need_to_spawn()) tank.second->spawn(this->generate_pos());
        else tank.second->update(dt);
    }

    BulletsManager::update(dt);
    this->handleKills();

    if(this->isFinished()) {
        this->finish(); //All the variable are destroyed by this call, so you need to stop here
        return;
    }

    //Hud
    hud->update();
}

void Melee::handleKills()
{
    while(!kills.empty())
    {
        //Points counting
        scores[kills.top().killer]["kills"] += 1;
        scores[kills.top().victim]["deaths"] += 1;

        //Message
        std::pair<sf::String, sf::Color> names[2];
        names[0] = {kills.top().victim, tanks[kills.top().victim]->getColorName()};
        names[1] = {kills.top().killer, tanks[kills.top().killer]->getColorName()};
        hud->addMessage(" was killed by ", names);

        kills.pop();

        //Update ranking of HUD
        this->orderBestPlayers();
        std::pair<std::pair<sf::String, sf::Color>, int> bests[3];
        for(uint a(0); a < 3; a++) {
            sf::Color color = (!bestPlayers[a].isEmpty()) ? tanks[bestPlayers[a]]->getColorName() : sf::Color::Black;
            bests[a] = {{bestPlayers[a], color}, scores[bestPlayers[a]]["kills"]};
        }
        hud->setBests(bests);
    }
}

void Melee::orderBestPlayers() {
    bool changed(true);
    while(changed) {
        changed = false;
        for(auto& player : scores) {
            sf::String const& name = player.first;
            int const& killsNumber = player.second["kills"];

            if(name != bestPlayers[0] && killsNumber > scores[bestPlayers[0]]["kills"]) {
                bestPlayers[0] = name;
                bestPlayers[1] = "";
                bestPlayers[2] = "";
                changed = true;
                break;
            } else if(name != bestPlayers[0] && name != bestPlayers[1] && killsNumber > scores[bestPlayers[1]]["kills"]) {
                bestPlayers[1] = name;
                bestPlayers[2] = "";
                changed = true;
                break;
            } else if(name != bestPlayers[0] && name != bestPlayers[1] && name != bestPlayers[2] && killsNumber > scores[bestPlayers[2]]["kills"]) {
                bestPlayers[2] = name;
            }
        }
    }
}

bool Melee::isFinished() {
    return ((!bestPlayers[0].isEmpty() && scores[bestPlayers[0]]["kills"] >= MAX_KILLS) || (hud->getTime().asSeconds() >= MAX_TIME));
}
