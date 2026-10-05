//
//  main.cpp
//  EPet
//
//  Created by marina porkhunova on 27.11.2023.
//

#include <stdio.h>
#include <iostream>

#include "Game.hpp"
#include "HamsterGame.hpp"

#include "Logger.hpp"

int main(int argc, const char *argv[]) {
    
    Logger::Instance().Init();
    
    Game& myGame = Game::Instance();
    if(!myGame.Init())
    {
        return -1;
    }
    
    if(!HamsterGame::Instance().Init(myGame.GetResourceManager()))
    {
        return -1;
    }
    
    myGame.Start("scene2"); // TODO: change to abstruct scene name
    myGame.Loop();
    myGame.Deinit();

    return 0;
}
