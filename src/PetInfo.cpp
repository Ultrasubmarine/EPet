//
//  PetInfo.cpp
//  EPet
//
//  Created by marina porkhunova on 17.12.2023.
//

#include "PetInfo.hpp"


void PetInfo::SetAvatar(std::string& avatar)
{
    _avatar = avatar;
}

void PetInfo::SetHappy(int happy)
{
    if(happy >=0 && happy <= _happyMax)
    {
        _happy = happy;
    }
    // log about problem
}

void PetInfo::SetFood(int food)
{
    if(food >=0 && food <= _foodMax)
    {
        _food = food;
    }
    // log about problem
}

void PetInfo::SetYear(int year)
{
    if(year >=0)
    {
        _year = year;
    }
    // log about problem
}
