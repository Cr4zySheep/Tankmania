#include "GameMode/Melee.hpp"

int main()
{
    srand(time(nullptr));

    Game game;
    try {
        game.changeState(new Melee(&game));

        game.gameLoop();
    }
    catch(std::exception& err)
    {
        std::cerr << err.what() << std::endl;
    }

    return 0;
}
