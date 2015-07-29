#ifndef TEXTUREMANAGER_HPP_INCLUDED
#define TEXTUREMANAGER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class TextureManager
{
private:

    std::map<std::string, sf::Texture> textures;

public:
    //Constructeur
    TextureManager()
    {
    }

    //Charge une texture et l'ajoute à la liste
    void loadTexture(std::string const& name, std::string const& filename);

    //Retourne une référence vers la texture demandée
    sf::Texture& getRef(std::string const& name);
};

#endif // TEXTUREMANAGER_HPP_INCLUDED
