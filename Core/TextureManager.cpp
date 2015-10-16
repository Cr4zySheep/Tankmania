#include "TextureManager.hpp"
using namespace std;

void TextureManager::loadTexture(sf::String const& name, sf::String const& filename)
{
    //Chargement
    sf::Texture tex;
    tex.loadFromFile(filename);
    tex.setRepeated(true);

    //Ajout à la liste
    textures[name] = tex;

    return;
}

sf::Texture& TextureManager::getRef(sf::String const& name)
{
    return textures.at(name);
}
