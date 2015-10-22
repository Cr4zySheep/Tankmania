#ifndef MAINSCREEN_HPP_INCLUDED
#define MAINSCREEN_HPP_INCLUDED

#include "GameMode/Melee.hpp"
#include "Core/Button.hpp"
#include "Core/Loader.hpp"

class MainScreen : public GameState {
private:
    Label title;
    Label version;
    Button start;
    Button quit;

    sf::Sprite background;

    Loader<sf::Texture> textureLoader;
    Loader<sf::Font> fontLoader;

public:
    MainScreen(Game* game);
    ~MainScreen();

    virtual void handleInput();
    virtual void update(float dt);
    virtual void draw();
};

#endif // MAINSCREEN_HPP_INCLUDED
