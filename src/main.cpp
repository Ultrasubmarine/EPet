//
//  main.cpp
//  EPet
//
//  Created by marina porkhunova on 27.11.2023.
//

#include "registry.hpp"
#include <iostream>
#include <thread>

#include "Game.hpp"

struct position{
    int y;
};

int main(int argc, const char *argv[]) {
    Game myGame;
    
    entt::registry reg;
    auto ent = reg.create();
    
    reg.emplace<position>(ent, 666);
    
    for( auto [e, pos]: reg.view<position>().each())
    {
        std::cout<<"test pos: y=" << pos.y<<std::endl;
    }
    
    myGame.Loop();

    return 0;
}
