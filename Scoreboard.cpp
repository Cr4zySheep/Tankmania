#include "Scoreboard.hpp"

Scoreboard::Scoreboard(Game* game, std::map<sf::String, std::map<sf::String, int>> scores) {
    this->game = game;
    this->game->window.setView(this->game->window.getDefaultView());

    fontManager.loadFont("thickhead", "rsc/fonts/thickhead.ttf");
    sf::Font& font = fontManager.getRef("thickhead");

    //Get the biggest name
    const sf::String* longest_name = &scores.begin()->first;
    for(auto& player : scores) if(player.first.getSize() > longest_name->getSize()) {
        longest_name = &player.first;
    }

    //Rank players by their number of kills
    std::vector<std::pair<sf::String, int>> ranked_players;
    for(auto& player : scores) if(!player.first.isEmpty()) {
        //PREFER USE A SCORE THAN KILLS LATER
        ranked_players.push_back({player.first, player.second["kills"]}); //Fill the list
    }
    //Order the players by number of kills (score later)
    for(unsigned int a(0); a < ranked_players.size() - 1;) {
        std::cout << ranked_players[a].first.toAnsiString() << std::endl;
        if(ranked_players[a].second < ranked_players[a + 1].second) { //If next player have more kills than the one before
            //Exchange the 2 players
            std::pair<sf::String, int> best_player = ranked_players[a];
            ranked_players[a] = ranked_players[a + 1];
            ranked_players[a + 1] = best_player;

            //And restart to begin of the list
            a = 0;
        } else { //Else continue to compare players scores
            a++;
        }
    }

    unsigned int line(1);
    sf::Vector2f pos(0, 0);
    //Create the stats
    for(unsigned int a(0); a < ranked_players.size(); a++) {
        pos.y = line * 28;
        pos.x = longest_name->getSize() * 8 + 50;
        sf::String& name = ranked_players[a].first;

        this->addLabel(font, name, sf::Color::White, 24, pos); // Player username

        pos.x *= 2;

        //All stats
        this->checkAndAdd(font, "kills", pos, scores[name], "Kills", (line == 1));   //Number of kills
        this->checkAndAdd(font, "deaths", pos, scores[name], "Deaths", (line == 1)); //Number of deaths

        line++;
    }

    this->game->window.create({(unsigned int)pos.x + 100, (unsigned int)pos.y + 28*2, sf::VideoMode::getDesktopMode().bitsPerPixel}, "Tankmania", sf::Style::Close || sf::Style::Titlebar);
}


Scoreboard::~Scoreboard() {
}

void Scoreboard::checkAndAdd(sf::Font& font, sf::String field, sf::Vector2f& pos, std::map<sf::String, int>& data, sf::String nameField, bool needNameField) {
    if(data.find(field) != data.end()) {
        pos.x += 100;
        this->addLabel(font, Str::convert(data[field]), sf::Color::White, 24, pos);
        if(needNameField) {
            this->addLabel(font, nameField, sf::Color::White, 24, {pos.x, 0});
        }
    }
}

void Scoreboard::addLabel(sf::Font& font, sf::String text, sf::Color color, unsigned int size, sf::Vector2f pos) {
    labels.push_back(Label(ALIGN_CENTER));
    Label& label = labels.back();
    label.setFont(font);
    label.modifyText(text, color, size);
    label.setPosition(pos.x, pos.y);
}

void Scoreboard::handleInput() {
    sf::Event event;
    while(game->window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            game->window.close();
            break;

        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::Escape) game->window.close();
            break;
        }
    }
}

void Scoreboard::update(float dt) {

}

void Scoreboard::draw() {
    for(auto& label : labels) {
        label.draw(game->window);
    }
}
