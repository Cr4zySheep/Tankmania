#ifndef Game_HPP_INCLUDED
#define Game_HPP_INCLUDED

#include <SFML/graphics.hpp>
#include <stack>
#include <iostream>

class GameState;

class Game
{
private:

    //Contient les GameState en cours d'utilisation
    std::stack<GameState*> statesList;

public:
    //Fenetre
    sf::RenderWindow window;

    /**
     * Constructeurs
     */
    Game();

    /**
     * Destructeurs
     */
    ~Game();

    /** @brief Ajoute un GameState à la liste actuelle
     *
     * @param GameState* GameState à ajouter
     * @return void
     */
    void addState(GameState* state);

    /** @brief Supprime le dernier GameState ajouté
     *
     * @return void
     */
    void removeState();

    /** @brief Remplace le GameState actuel par celui passé en paramètre
     *
     * @param GameState* nouveau GameState
     * @return void
     */
    void changeState(GameState* state);

    /** @brief Retourne un pointeur vers le dernier GameState
     *
     * @return Pointeur vers le dernier GameState
     */
    GameState* peekState() const;

    /** @brief Boucle principale du programme
     *
     * @return void
     */
    void gameLoop();

};

#endif // Game_HPP_INCLUDED
