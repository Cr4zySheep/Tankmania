#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED

#include "Game.hpp"

class GameState
{
public:
    Game* game;

    //Constructeur
    GameState() {};
    //Destructeur
    virtual ~GameState() {};

    /** @brief Affiche les éléments
     *
     * @param dt temps écoulé depuis le dernier appel
     */
    virtual void draw() = 0;

    /** @brief Mets à jour les éléments
     *
     * @param dt temps écoulé depuis le dernier appel
     */
    virtual void update(float dt) = 0;

    /** @brief Gère les évènements
     */
    virtual void handleInput() = 0;

};

#endif // GAMESTATE_HPP_INCLUDED
