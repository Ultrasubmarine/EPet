//
//  main.cpp
//  EPet
//
//  Created by marina porkhunova on 27.11.2023.
//

#include <iostream>
#include <thread>

#include "Game.hpp"
#include "Input.hpp"

void MainThread(Input* i)
{
    Game myGame;
    myGame.Loop(i);
}

void InputThread(Input* i)
{
    char c = ' ';
    while(c != 'a')
    {
        c = std::getchar();
        i->AddEvent(c);
    }
}

int main(int argc, const char * argv[])
{
    Input* my = new Input();
    
    std::thread inputThread(&InputThread, my);
    std::thread mainThread(&MainThread, my);
    
    mainThread.join();
    inputThread.join();
    
    delete my;
    return 0;
}
