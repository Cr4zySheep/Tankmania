#ifndef FONTMANAGER_HPP_INCLUDED
#define FONTMANAGER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class FontManager
{
private:
    std::map<std::string, sf::Font> fonts;

public:
    //Constructeur
    FontManager()
    {
    }

    //Charge une Font et l'ajoute à la liste
    void loadFont(std::string const& name, std::string const& filename);

    //Retourne une référence vers la Font demandée
    sf::Font& getRef(std::string const& name);
};

#endif // FONTMANAGER_HPP_INCLUDED
