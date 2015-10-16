#include "Scoreboard.hpp"

Scoreboard::Scoreboard(Game* game, std::map<sf::String, std::map<sf::String, int>> scores) {
    this->game = game;
    this->game->window.setView(this->game->window.getDefaultView());

    fontManager.loadFont("thickhead", "rsc/fonts/thickhead.ttf");
    sf::Font& font = fontManager.getRef("thickhead");

    //Get the biggest name
    const sf::String* name = &scores.begin()->first;
    for(auto& player : scores) if(player.first.getSize() > name->getSize()) {
        name = &player.first;
    }

    unsigned int line(1);
    float y;
    float x;
    //Create the stats
    for(auto& player : scores) if(!player.first.isEmpty()) {
        y = line * 28;
        x = name->getSize() * 8 + 50;
        this->addLabel(font, player.first, sf::Color::White, 24, {x, y}); // Player username

        x *= 2;

        //All stats
        for(auto& stat : player.second) if(!stat.first.isEmpty()) {
            x += 100;
            this->addLabel(font, Str::convert(stat.second), sf::Color::White, 24, {x, y});
            if(line == 1) {
                this->addLabel(font, stat.first, sf::Color::White, 24, {x, 0});
            }
        }

        line++;
    }

    this->game->window.create({(unsigned int)x + 100, (unsigned int)y + 28*2, sf::VideoMode::getDesktopMode().bitsPerPixel}, "Tankmania", sf::Style::Close || sf::Style::Titlebar);
}


Scoreboard::~Scoreboard() {
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
