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

enum PetParameters
{
    Food,
    Happy,
    Year
};

class PetInfo : public Singleton<PetInfo>
{
    class _Parametr
    {
        int _parametr;
        const int _max;
        const int _min;

    public:
        _Parametr(int value, int max, int min = 0);
        
        bool Increase();
        bool Decrease();
        
        int Get() const { return _parametr;};
        int GetMax() const { return _max;};
        int GetMin() const { return _min;};
        
        bool Set(int value);
    };
    
    std::map<PetParameters, _Parametr> _parametrs;
    std::map<PetParameters, Signal<int> > _parametrsSignals;
    std::string _avatar;
    
protected:
    PetInfo();
    ~PetInfo() = default;
    
public:

    const int GetParametr(PetParameters name) const;
    const int GetParametrMax(PetParameters name) const;
    const int GetParametrMin(PetParameters name) const;
    
    bool SetParametr(PetParameters name, int value);
    
    bool DecreaseParametr(PetParameters name);
    bool IncreaseParametr(PetParameters name);
    
    const std::string& GetAvatar() const { return _avatar;};
    void SetAvatar(std::string& avatar);
    
    Signal<int>* GetParameterSignal(PetParameters name);
    
    //TODO: add functions Save() Load()
    friend Singleton<PetInfo>;
};
#endif /* PetStats_hpp */
