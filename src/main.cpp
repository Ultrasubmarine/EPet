//
//  main.cpp
//  EPet
//
//  Created by marina porkhunova on 27.11.2023.
//

#include "Game.hpp"
#include <stdio.h>
#include <iostream>
#include "Logging.hpp"

int main(int argc, const char *argv[]) {
    
    Logger::Instance().Initialize();
    
    Game& myGame = Game::Instance();
    
    if(!myGame.Init())
    {
        return -1;
    }
    
    myGame.Loop();
    myGame.Deinit();

    return 0;
}
