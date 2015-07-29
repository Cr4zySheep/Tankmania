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

    /** @brief Affiche les �l�ments
     *
     * @param dt temps �coul� depuis le dernier appel
     */
    virtual void draw() = 0;

    /** @brief Mets � jour les �l�ments
     *
     * @param dt temps �coul� depuis le dernier appel
     */
    virtual void update(float dt) = 0;

    /** @brief G�re les �v�nements
     */
    virtual void handleInput() = 0;

};

#endif // GAMESTATE_HPP_INCLUDED
