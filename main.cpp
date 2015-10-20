#include "MainScreen.hpp"

int main()
{
    srand(time(nullptr));

    Game game;
    try {
        game.changeState(new MainScreen(&game));

        game.gameLoop();
    }
    catch(std::exception& err)
    {
        std::cerr << err.what() << std::endl;
    }

    return 0;
}
