#ifndef APP_HPP_INCLUDED
#define APP_HPP_INCLUDED

#include "Core/Loader.hpp"
#include "BulletsManager.hpp"

struct App {
    Loader<sf::Texture> textureLoader;
    Loader<sf::Font> fontLoader;
    BulletsManager bulletsManager;
};

#endif // APP_HPP_INCLUDED
