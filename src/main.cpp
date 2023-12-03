//
//  main.cpp
//  EPet
//
//  Created by marina porkhunova on 27.11.2023.
//

#include <iostream>
#include "Game.hpp"

int main(int argc, const char * argv[]) {
  
    Game myGame;
    system("clear");

    
    //TODO ADD thread to not blocking input
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
