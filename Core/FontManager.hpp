#ifndef FONTMANAGER_HPP_INCLUDED
#define FONTMANAGER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <map>

class FontManager
{
private:
    std::map<sf::String, sf::Font> fonts;

public:
    //Constructeur
    FontManager()
    {
    }

    //Charge une Font et l'ajoute � la liste
    void loadFont(sf::String const& name, sf::String const& filename);

    //Retourne une r�f�rence vers la Font demand�e
    sf::Font& getRef(sf::String const& name);
};

#endif // FONTMANAGER_HPP_INCLUDED
