#include "MainScreen.hpp"

MainScreen::MainScreen(Game* game) : title(ALIGN_CENTER), version(ALIGN_RIGHT), start(ALIGN_CENTER), quit(ALIGN_CENTER) {
    this->game = game;

    fontManager.loadFont("thickhead", "rsc/fonts/thickhead.ttf");
    sf::Font& font = fontManager.getRef("thickhead");

    textureManager.loadTexture("background", "rsc/backgrounds/mainscreen.png");

    //Background
    background.setTexture(textureManager.getRef("background"));

    //Title bar
    title.setFont(font);
    title.modifyText("Tankmania", sf::Color::Black, 72);
    title.setPosition(720 / 2, 10);

    //Current version
    version.setFont(font);
    sf::String currentVersion = "1.01";
    version.modifyText(currentVersion, sf::Color::Black, 24);
    version.setPosition(720 - 10, 480 - 34);

    //Button start
    start.setFont(font);
    start.setTexts("start", "START", 48, sf::Color::Black);
    start.setPosition(720 / 2, 480 / 2 - 48 * 1);

    //Button quit
    quit.setFont(font);
    quit.setTexts("exit", "EXIT", 48, sf::Color::Black);
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
    }
    start.handleInput(game->window);
    quit.handleInput(game->window);
}

void MainScreen::update(float dt) {
    start.update();
    quit.update();
    if(start.getClicked()) {
        game->changeState(new Melee(game));
        return;
    }
    if(quit.getClicked()) {
        game->window.close();
        return;
    }
}

void MainScreen::draw() {
    game->window.draw(background);
    title.draw(game->window);
    version.draw(game->window);
    start.draw(game->window);
    quit.draw(game->window);
}
