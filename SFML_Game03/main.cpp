#include <iostream>
#include "Game.h"

int main()
{

    //init srand
    std::srand(static_cast<unsigned>(time(NULL)));

    // init game engine
   Game game;

   game.run();


    return 0;
}
