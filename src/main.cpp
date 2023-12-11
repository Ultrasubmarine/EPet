//
//  main.cpp
//  EPet
//
//  Created by marina porkhunova on 27.11.2023.
//

#include <iostream>
#include "Game.hpp"

class A
{
    int a=5;
public:
    ~A() { std::cout<<"A was deleted";};
};

int main(int argc, const char * argv[]) {
  
    Game myGame;
    system("clear");

    
    char x = 0;
    while(x != 'e')
    {
        myGame.Loop();
        
       // std::cin>>x;
        if(x == 'w')
            myGame.SetState(Game::State::Wait);
        if(x == 'a')
            myGame.SetState(Game::State::Active);
        
  
    }
    return 0;
}
