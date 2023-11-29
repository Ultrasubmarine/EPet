//
//  main.cpp
//  EPet
//
//  Created by marina porkhunova on 27.11.2023.
//

#include <iostream>
#include "Game.hpp"


int main(int argc, const char * argv[]) {
    // insert code here...
    
    Game myGame;
    system("clear");

    char x = 0;
    while(x != 'e')
    {
        myGame.Loop();
        
        std::cin>>x;
        if(x == 'w')
            myGame.SetState(Game::State::Wait);
        if(x == 'a')
            myGame.SetState(Game::State::Active);
    }
    return 0;
}
