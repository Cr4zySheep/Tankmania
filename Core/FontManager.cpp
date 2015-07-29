#include "FontManager.hpp"
using namespace std;

void FontManager::loadFont(std::string const& name, std::string const& filename)
{
    //Chargement
    sf::Font font;
    font.loadFromFile(filename);

    //Ajout à la liste
    fonts[name] = font;

    return;
}

sf::Font& FontManager::getRef(std::string const& name)
{
    return fonts.at(name);
}
