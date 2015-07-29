#include "Game.hpp"
#include "GameState.hpp"

using namespace std;

Game::Game() : window(sf::VideoMode(window_width, window_height), "Tankmania", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize)
{
    window.setFramerateLimit(60);
}

Game::~Game()
{
    while(!statesList.empty()) removeState();
}

void Game::addState(GameState* state)
{
    statesList.push(state);

    return;
}

void Game::removeState()
{
    if(!statesList.empty())
    {
        delete statesList.top();
        statesList.pop();
    }

    return;
}

void Game::changeState(GameState* state)
{
    if(!statesList.empty())
    {
        removeState();
    }
    addState(state);

    return;
}

GameState* Game::peekState() const
{
    if(statesList.empty()) return nullptr;
    return statesList.top();
}

void Game::gameLoop()
{
    sf::Clock clock;

    while(window.isOpen())
    {
        sf::Time elapsed(clock.restart());
        float dt = elapsed.asSeconds();

        if(peekState() == nullptr) continue;
        peekState()->handleInput();
        peekState()->update(dt);
        window.clear(sf::Color::Black);
        peekState()->draw();
        window.display();
    }

    return;
}
