//
//  main.cpp
//  EPet
//
//  Created by marina porkhunova on 27.11.2023.
//

#include <iostream>
#include <thread>

#include "Game.hpp"


int main(int argc, const char *argv[]) {
    Game myGame;
    myGame.Loop();
    
    return 0;
}
