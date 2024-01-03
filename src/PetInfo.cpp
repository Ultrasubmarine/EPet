//
//  PetInfo.cpp
//  EPet
//
//  Created by marina porkhunova on 17.12.2023.
//

#include "PetInfo.hpp"


PetInfo::_Parametr::_Parametr(int value, int max, int min) : _max(max), _min(min), _parametr(0)
{
    Set(value);
}

bool PetInfo::_Parametr::Increase()
{
    if(_parametr < _max)
    {
        _parametr++;
        return true;
    }
    return false;
}

bool PetInfo::_Parametr::Decrease()
{
    if(_parametr > _min)
    {
        _parametr--;
        return true;
    }
    return false;
}

bool PetInfo::_Parametr::Set(int value)
{
    if(value <= _max && value >= _min)
    {
        _parametr = value;
        return true;
    }
    return false;
}


PetInfo::PetInfo()
{
    _parametrs.insert({Happy, _Parametr(5,5)});
    _parametrs.insert({Food, _Parametr(4,5)});
    _parametrs.insert({Year, _Parametr(1,INT_MAX)});
}

void PetInfo::SetAvatar(std::string& avatar)
{
    _avatar = avatar;
}

const int PetInfo::GetParametr(PetParameters name) const
{
    if(auto it = _parametrs.find(name); it != _parametrs.end())
    {
        return it->second.Get();
    }
    return -1;
}

const int PetInfo::GetParametrMax(PetParameters name) const
{
    if(auto it = _parametrs.find(name); it != _parametrs.end())
    {
        return it->second.GetMax();
    }
    return -1;
}

const int PetInfo::GetParametrMin(PetParameters name) const
{
    if(auto it = _parametrs.find(name); it != _parametrs.end())
    {
        return it->second.GetMin();
    }
    return -1;
}

bool PetInfo::DecreaseParametr(PetParameters name)
{
    if(auto it = _parametrs.find(name); it != _parametrs.end())
    {
        return it->second.Decrease();
    }
    return false;
}

bool PetInfo::IncreaseParametr(PetParameters name)
{
    if(auto it = _parametrs.find(name); it != _parametrs.end())
    {
        return it->second.Increase();
    }
    return false;
}

