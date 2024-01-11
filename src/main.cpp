//
//  main.cpp
//  EPet
//
//  Created by marina porkhunova on 27.11.2023.
//

#include <iostream>
#include "Game.hpp"
#include "PetInfo.hpp"
#include <thread>
#include <mutex>

void Input()
{
    while(true)
    {
        char c;
        std::cin>>c;
        std::cout<<"print: "<<c<<std::endl;
    }
}

void Loop()
{
    Game myGame;
    myGame.Loop();
}

int main(int argc, const char * argv[])
{
    std::thread inputThread(&Input);
    std::thread gameThread(&Loop);
    
    inputThread.join();
    gameThread.join();
   
    return 0;
}
