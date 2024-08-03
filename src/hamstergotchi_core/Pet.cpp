//
//
//  PetInfo.cpp
//  EPet
//
//  Created by marina porkhunova on 17.12.2023.
//

#include "Pet.hpp"

Pet::_ParameterData::_ParameterData(int value, int max, int min) : _max(max), _min(min), _current(0)
{
    Set(value);
}

bool Pet::_ParameterData::Increase(int increaseValue)
{
    if(_current == _max)
    {
        return false;
    }
    else
    {
        _current = _current + increaseValue >= _max? _max: _current + increaseValue;
        return true;
    }
}

bool Pet::_ParameterData::Decrease(int decreaseValue)
{
    if(_current == _min)
    {
        return false;
    }
    else
    {
        _current = _current - decreaseValue <= _min? _min: _current - decreaseValue;
        return true;
    }
}

bool Pet::_ParameterData::Set(int value)
{
    if(value <= _max && value >= _min)
    {
        _current = value;
        return true;
    }
    return false;
}


Pet::Pet()
{
    _parametrs.insert({Happy, _ParameterData(5,5)});
    _parametrsSignals.insert({Happy, Signal<int>()});
    
    _parametrs.insert({Food, _ParameterData(4,5)});
    _parametrsSignals.insert({Food, Signal<int>()});
    
    _parametrs.insert({Year, _ParameterData(1,INT_MAX)});
    _parametrsSignals.insert({Year, Signal<int>()});
}

const int Pet::GetParametr(Parameter name) const
{
    if(auto it = _parametrs.find(name); it != _parametrs.end())
    {
        return it->second.Get();
    }
    return -1;
}

const int Pet::GetParametrMax(Parameter name) const
{
    if(auto it = _parametrs.find(name); it != _parametrs.end())
    {
        return it->second.GetMax();
    }
    return -1;
}

const int Pet::GetParametrMin(Parameter name) const
{
    if(auto it = _parametrs.find(name); it != _parametrs.end())
    {
        return it->second.GetMin();
    }
    return -1;
}

bool Pet::SetParametr(Parameter name, int value)
{
    if(auto it = _parametrs.find(name); it != _parametrs.end())
    {
        auto change = it->second.Set(value);
        if(change)
        {
            _parametrsSignals[name].Broadcast(it->second.Get());
        }
        return change;
    }
    return false;
}

bool Pet::DecreaseParametr(Parameter name, int decreaseValue)
{
    if(auto it = _parametrs.find(name); it != _parametrs.end())
    {
        auto change = it->second.Decrease(decreaseValue);
        if(change)
        {
            _parametrsSignals[name].Broadcast(it->second.Get());
        }
        return change;
    }
    return false;
}

bool Pet::IncreaseParametr(Parameter name, int increaseValue)
{
    if(auto it = _parametrs.find(name); it != _parametrs.end())
    {
        auto change = it->second.Increase(increaseValue);
        if(change)
        {
            _parametrsSignals[name].Broadcast(it->second.Get());
        }
        return change;
    }
    return false;
}

Signal<int>* Pet::GetParameterSignal(Parameter name)
{
    if(auto it = _parametrsSignals.find(name); it != _parametrsSignals.end())
    {
        return &it->second;
    }
    return nullptr;
}
