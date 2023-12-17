//
//  main.cpp
//  EPet
//
//  Created by marina porkhunova on 27.11.2023.
//

#include <iostream>
#include "Game.hpp"
#include "PetInfo.hpp"


int main(int argc, const char * argv[]) {
  
    Game myGame;
    
    char x = 0;
    while(x != 'e')
    {
        myGame.Loop();
        std::cin>>x;
    }
    return 0;
}
