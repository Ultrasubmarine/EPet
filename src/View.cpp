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
    if(PetInfo::Instance().GetIsLive())
    {
    //DEFAULT HUMSTER TAMAGOTCHI AVATAR
    printf("-----------------\n\n\n%s ^  ^\n%s(. .)          \n\n   I'm awake :)\n\n-----------------",_tab.c_str(),_tab.c_str());
    }
    else
    {
        printf("-----------------\n\n\n%s ^  ^\n%s(x x)          \n\n   I'm dead :(\n\n-----------------",_tab.c_str(),_tab.c_str());
    }
    
    //Draw Tamagotchi stats
    std::cout <<"\n   PET STATS:   \n";
    std::cout <<"   Happy:" << PetInfo::Instance().GetParametr(Happy)<<"/"<<PetInfo::Instance().GetParametrMax(Happy)<<std::endl;
    std::cout <<"   Food:" << PetInfo::Instance().GetParametr(Food)<<"/"<<PetInfo::Instance().GetParametrMax(Food)<<std::endl;
    std::cout <<"   year: "<< PetInfo::Instance().GetParametr(Year)<<std::endl;
  //  std::cout << PetInfo::Instance().GetAvatar();
};

void View::Update()
{
    if(PetInfo::Instance().GetIsLive())
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
