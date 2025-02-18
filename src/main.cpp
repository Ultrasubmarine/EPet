//
//  main.cpp
//  EPet
//
//  Created by marina porkhunova on 27.11.2023.
//

#include "Game.hpp"
#include <stdio.h>
#include <iostream>

enum Color
{
    red = 1,
    blue,
    white
};

enum Animal
{
    cat = 1,
    rabbit,
    dog
};

enum class ColorClass
{
    red = 1,
    blue,
    white
};

int main(int argc, const char *argv[]) {
    
//    int b = 2;
//    Color favoriteColor = static_cast<Color>(b);
//    
//   // Color favoriteColor2 = b; // error. doesn't work use int with enum
//   // Color favoriteColor = ColorClass::red; // error. doesn't work use int with enum
//    Color favoriteColor3 = static_cast<Color>(ColorClass::red);
//    
//    ColorClass favoriteColorClass = ColorClass::red;
//    ColorClass favoriteColorClass2 = static_cast<ColorClass>(1);
//    int myInt = static_cast<int>(ColorClass::red);
//    
//    
//    
//    int intFromEnum = favoriteColor;
//    //int intFromEnumClass = favoriteColorClass; // good error
//    
//    std::cout<<favoriteColor<<std::endl;
//    
//    if( favoriteColor == Animal::rabbit)
//    {
//        std::cout<<"my favorite color is rabbit"<<std::endl;
//    }
//    if( Animal::cat == Color::red)
//    {
//        std::cout<<"my favorite color is rabbit"<<std::endl;
//    }

    Game myGame;
    
    if(!myGame.Init())
    {
        return -1;
    }
    
    
    myGame.Loop();
    myGame.Deinit();
    
    return 0;
}
