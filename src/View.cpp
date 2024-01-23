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
    switch ( PetInfo::Instance().GetState()) {
        case PetState::usual:
            //DEFAULT HUMSTER TAMAGOTCHI AVATAR
            printf("-----------------\n\n\n%s ^  ^\n%s(. %s.)          \n\n   I'm awake :)\n\n-----------------",_tab.c_str(), _tab.c_str(), _size.c_str());
            break;
        case PetState::sleep:
            printf("-----------------\n\n\n%s ^  ^\n%s(- %s-) zZz      \n\n   --zzz--    \n\n-----------------",_tab.c_str(), _tab.c_str(), _size.c_str());
            break;
        case PetState::dead:
            printf("-----------------\n\n\n%s ^  ^\n%s(x %sx)          \n\n   I'm dead :(\n\n-----------------",_tab.c_str(), _tab.c_str(), _size.c_str());
            break;
        default:
            break;
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
    if(PetInfo::Instance().GetState() == PetState::usual)
        CalculateAnimation();
    
    if( PetInfo::Instance().GetParametr(Year) >= 2 )
        _size = " ";
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
