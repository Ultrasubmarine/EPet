//
//  View.cpp
//  EPet
//
//  Created by marina porkhunova on 17.12.2023.
//

#include <iostream>

#include "View.hpp"
#include "PetInfo.hpp"

void View::Draw()
{
    //DEFAULT HUMSTER TAMAGOTCHI AVATAR
    printf("-----------------\n\n\n%s ^  ^\n%s(. .)          \n\n   I'm awake :)\n\n-----------------",_tab.c_str(),_tab.c_str());
    
    
  //  std::cout << PetInfo::Instance().GetAvatar();
};

void View::Update()
{
    CalculateAnimation();
};


void View::CalculateAnimation()
{
    if(_moveRignt)
    {
        _tab +=" ";
    }
    else
    {
        _tab.pop_back();
    }
        
        
    if(_moveRignt && _tab.size() > 12)
    {
        _moveRignt= false;
    }
    if(!_moveRignt && _tab.size() == 0)
    {
        _moveRignt= true;
    }
}
