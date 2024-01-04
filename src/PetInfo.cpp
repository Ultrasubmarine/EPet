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
    _parametrsSignals.insert({Happy, Signal<int>()});
    
    _parametrs.insert({Food, _Parametr(4,5)});
    _parametrsSignals.insert({Food, Signal<int>()});
    
    _parametrs.insert({Year, _Parametr(1,INT_MAX)});
    _parametrsSignals.insert({Year, Signal<int>()});
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

bool PetInfo::SetParametr(PetParameters name, int value)
{
    if(auto it = _parametrs.find(name); it != _parametrs.end())
    {
        auto change = it->second.Set(value);
        if(change)
        {
           // _parametrsSignals[name].Broadcast(it->second.Get());
        }
        return change;
    }
    return false;
}

bool PetInfo::DecreaseParametr(PetParameters name)
{
    if(auto it = _parametrs.find(name); it != _parametrs.end())
    {
        auto change = it->second.Decrease();
        if(change)
        {
         //   _parametrsSignals[name].Broadcast(it->second.Get());
        }
        return change;
    }
    return false;
}

bool PetInfo::IncreaseParametr(PetParameters name)
{
    if(auto it = _parametrs.find(name); it != _parametrs.end())
    {
        auto change = it->second.Increase();
        if(change)
        {
         //   _parametrsSignals[name].Broadcast(it->second.Get());
        }
        return change;
    }
    return false;
}

Signal<int>* PetInfo::GetParameterSignal(PetParameters name)
{
    if(auto it = _parametrsSignals.find(name); it != _parametrsSignals.end())
    {
        return &it->second;
    }
    return nullptr;
}
