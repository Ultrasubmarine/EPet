//
//  main.cpp
//  EPet
//
//  Created by marina porkhunova on 27.11.2023.
//

#include "Game.hpp"
#include <stdio.h>
#include <iostream>

template<class T>
T testFunction(T n)
{
    //std::cout<<n;
};

int main(int argc, const char *argv[]) {
    
    Game myGame;
    
    if(!myGame.Init())
    {
        return -1;
    }
    
    
    myGame.Loop();
    myGame.Deinit();
    
    return 0;
}
