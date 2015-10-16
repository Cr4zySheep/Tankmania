#ifndef TEXTUREMANAGER_HPP_INCLUDED
#define TEXTUREMANAGER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class TextureManager
{
private:

    std::map<sf::String, sf::Texture> textures;

public:
    //Constructeur
    TextureManager()
    {
    }

    //Charge une texture et l'ajoute � la liste
    void loadTexture(sf::String const& name, sf::String const& filename);

    //Retourne une r�f�rence vers la texture demand�e
    sf::Texture& getRef(sf::String const& name);
};

#endif // TEXTUREMANAGER_HPP_INCLUDED
