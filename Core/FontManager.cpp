#include "FontManager.hpp"
using namespace std;

void FontManager::loadFont(sf::String const& name, sf::String const& filename)
{
    //Chargement
    sf::Font font;
    font.loadFromFile(filename);

    //Ajout à la liste
    fonts[name] = font;

    return;
}

sf::Font& FontManager::getRef(sf::String const& name)
{
    return fonts.at(name);
}
