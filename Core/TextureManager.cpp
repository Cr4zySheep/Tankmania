#include "TextureManager.hpp"
using namespace std;

void TextureManager::loadTexture(std::string const& name, std::string const& filename)
{
    //Chargement
    sf::Texture tex;
    tex.loadFromFile(filename);
    tex.setRepeated(true);

    //Ajout à la liste
    textures[name] = tex;

    return;
}

sf::Texture& TextureManager::getRef(std::string const& name)
{
    return textures.at(name);
}
