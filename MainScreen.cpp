#include "MainScreen.hpp"

MainScreen::MainScreen(Game* game) : title(ALIGN_CENTER), version(ALIGN_RIGHT), start(ALIGN_CENTER), quit(ALIGN_CENTER) {
    this->game = game;

    fontLoader.load("thickhead", "rsc/fonts/thickhead.ttf");
    sf::Font& font = fontLoader.getRef("thickhead");

    textureLoader.load("background", "rsc/backgrounds/mainscreen.png");

    //Background
    background.setTexture(textureLoader.getRef("background"));

    //Title bar
    title.setFont(font);
    title.setText({"Tankmania", sf::Color::Black, 72});
    title.setPosition(720 / 2, 10);

    //Current version
    version.setFont(font);
    sf::String currentVersion = "1.01.002";
    version.setText({currentVersion, sf::Color::Black, 24});
    version.setPosition(720 - 10, 480 - 34);

    //Button start
    start.setFont(font);
    start.setLabels({"start", sf::Color::Black, 48}, {"START", sf::Color::Black, 48});
    start.setPosition(720 / 2, 480 / 2 - 48 * 1);

    //Button quit
    quit.setFont(font);
    quit.setLabels({"exit", sf::Color::Black, 48}, {"EXIT", sf::Color::Black, 48});
    quit.setPosition(720 / 2, 480 / 2 + 48 * 2);

    this->game->window.create({720, 480, sf::VideoMode::getDesktopMode().bitsPerPixel}, "Tankmania", sf::Style::Default);
    this->game->window.setMouseCursorVisible(true);
}

MainScreen::~MainScreen() {
}

void MainScreen::handleInput() {
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

        start.handleInput(event);
        quit.handleInput(event);
    }
}

void MainScreen::update(float dt) {
    start.update();
    quit.update();
    if(start.getState(CLICKED)) {
        game->changeState(new Melee(game));
        return;
    }
    if(quit.getState(CLICKED)) {
        game->window.close();
        return;
    }
}

void MainScreen::draw() {
    game->window.draw(background);
    game->window.draw(title);
    game->window.draw(version);
    game->window.draw(start);
    game->window.draw(quit);
}
