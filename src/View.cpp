//
//  View.cpp
//  EPet
//
//  Created by marina porkhunova on 17.12.2023.
//

#include <iostream>

#include "View.hpp"
#include "Pet.hpp"

void View::Draw()
{
    switch ( Pet::Instance().GetState())
    {
        case Pet::State::Usual:
            //DEFAULT HUMSTER TAMAGOTCHI AVATAR
            printf("-----------------\n\n\n%s ^  ^\n%s(. %s.)          \n\n   I'm awake :)\n\n-----------------",_tab.c_str(), _tab.c_str(), _size.c_str());
            break;
        case Pet::State::Sleep:
            printf("-----------------\n\n\n%s ^  ^\n%s(- %s-) zZz      \n\n   --zzz--    \n\n-----------------",_tab.c_str(), _tab.c_str(), _size.c_str());
            break;
        case Pet::State::Dead:
            printf("-----------------\n\n\n%s ^  ^\n%s(x %sx)          \n\n   I'm dead :(\n\n-----------------",_tab.c_str(), _tab.c_str(), _size.c_str());
            break;
        default:
            break;
    }

    //Draw Tamagotchi stats
    std::cout <<"\n   PET STATS:   \n";
    std::cout <<"   Happy:" << Pet::Instance().GetParametr(Pet::Happy)<<"/"<<Pet::Instance().GetParametrMax(Pet::Happy)<<std::endl;
    std::cout <<"   Food:" << Pet::Instance().GetParametr(Pet::Food)<<"/"<<Pet::Instance().GetParametrMax(Pet::Food)<<std::endl;
    std::cout <<"   year: "<< Pet::Instance().GetParametr(Pet::Year)<<std::endl;
};

void View::Update()
{
    if(Pet::Instance().GetState() == Pet::State::Usual)
    {
        CalculateAnimation();
    }
    
    if( Pet::Instance().GetParametr(Pet::Year) >= 2 )
    {
        _size = " ";
    }
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
