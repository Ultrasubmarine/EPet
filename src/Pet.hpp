//
//  PetInfo.hpp
//  EPet
//
//  Created by marina porkhunova on 17.12.2023.
//

#ifndef PetStats_hpp
#define PetStats_hpp

#include <stdio.h>
#include <string>
#include <map>

#include "Singleton.hpp"
#include "Subscription.hpp"

class Pet : public Singleton<Pet>
{
public:
    enum State
    {
        Usual,
        Sleep,
        Dead
    };
    
    enum Parameter
    {
        Food,
        Happy,
        Year
    };
 
private:
    class _ParameterData
    {
        int _current;
        const int _max;
        const int _min;
        
    public:
        _ParameterData(int value, int max, int min = 0);
        
        bool Increase(int increaseValue = 1);
        bool Decrease(int decreaseValue = 1);
        
        int Get() const { return _current;};
        int GetMax() const { return _max;};
        int GetMin() const { return _min;};
        
        bool Set(int value);
    };
    
    std::map<Parameter, _ParameterData> _parametrs;
    std::map<Parameter, Signal<int> > _parametrsSignals;
    
    State _state = State::Usual;
    
protected:
    Pet();
    ~Pet() = default;
    
public:
    const int GetParametr(Parameter name) const;
    const int GetParametrMax(Parameter name) const;
    const int GetParametrMin(Parameter name) const;
    
    bool SetParametr(Parameter name, int value);
    
    bool DecreaseParametr(Parameter name, int decreaseValue = 1);
    bool IncreaseParametr(Parameter name, int increaseValue = 1);
    
    void SetState(State state) { _state = state; };
    State GetState() const {return _state;};
    bool GetIsLive() const { return _state!= State::Dead;};
    
    Signal<int>* GetParameterSignal(Parameter name);
    
    //TODO: add functions Save() Load()
    friend Singleton<Pet>;
};
#endif /* PetStats_hpp */
