#include "Scoreboard.hpp"
#include "MainScreen.hpp"

Scoreboard::Scoreboard(Game* game, std::map<sf::String, std::map<sf::String, int>> scores, std::map<sf::String, sf::Color> colors) {
    this->game = game;
    this->game->window.setView(this->game->window.getDefaultView());

    //Load music
    if(theme.openFromFile("rsc/musics/score_theme.ogg")) {
        theme.setLoop(true);
        theme.play();
    }

    textureLoader.load("background", "rsc/backgrounds/scoreboard.png");
    background.setTexture(textureLoader.getRef("background"));

    fontLoader.load("thickhead", "rsc/fonts/thickhead.ttf");
    sf::Font& font = fontLoader.getRef("thickhead");

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
        pos.x = longest_name->getSize() * 8;
        sf::String& name = ranked_players[a].first;

        this->addLabel(font, name, colors[name], 24, pos); // Player username

        pos.x *= 2;
        pos.x += 50;

        //All stats
        this->checkAndAdd(font, "kills", pos, 150, scores[name], "Kills", (line == 1));   //Number of kills
        this->checkAndAdd(font, "deaths", pos, 100, scores[name], "Deaths", (line == 1)); //Number of deaths

        line++;
    }

    //Center label
    //TODO IF LARGER THAN WINDOW -> FULL SCREEN AND SAME PROCESS
    auto& lastElmtSize = labels.back().getPosition();
    float _x = (720 - lastElmtSize.x) / 2 - longest_name->getSize() * 4,
          _y = (480 - lastElmtSize.y) / 2 - 28;
    for(auto& label : labels) {
        label.setPosition(label.getPosition().x + _x,
                          label.getPosition().y + _y);
    }

    resume.setAlign(ALIGN_CENTER);
    resume.setFont(font);
    resume.setLabels({"resume", sf::Color::White, 36}, {"resume", {128, 108, 0, 255}, 36});
    resume.setPosition(720 / 2 + 25, 480 - 44);

    this->game->window.create({720, 480, sf::VideoMode::getDesktopMode().bitsPerPixel}, "Tankmania", sf::Style::Default);
    this->game->window.setMouseCursorVisible(true);
}


Scoreboard::~Scoreboard() {
}

void Scoreboard::checkAndAdd(sf::Font& font, sf::String field, sf::Vector2f& pos, float addToX, std::map<sf::String, int>& data, sf::String nameField, bool needNameField) {
    if(data.find(field) != data.end()) {
        this->addLabel(font, Str::convert(data[field]), sf::Color::White, 24, pos);
        if(needNameField) {
            this->addLabel(font, nameField, sf::Color::White, 24, {pos.x, 0});
        }
        pos.x += addToX;
    }
}

void Scoreboard::addLabel(sf::Font& font, sf::String text, sf::Color color, unsigned int size, sf::Vector2f pos) {
    labels.push_back(Label(ALIGN_CENTER));
    Label& label = labels.back();
    label.setFont(font);
    label.setText({text, color, size});
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
        resume.handleInput(event);
    }
}

void Scoreboard::update(float dt) {
    resume.update();
    if(resume.getState(CLICKED)) {
        game->changeState(new MainScreen(game));
        return;
    }
}

void Scoreboard::draw() {
    game->window.draw(background);
    for(auto& label : labels) {
        game->window.draw(label);
    }
    game->window.draw(resume);
}
