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

#include "Singleton.hpp"

class stat
{
    int _parametr;
    int _max;
    
    void OnChange();

public:
    bool Increase();
    bool Decrease();
    
    int Get();
    bool Set();
};

class PetInfo : public Singleton<PetInfo>
{
    int _food = 0;
    int _happy = 0;
    int _year = 0;
    
    const int _happyMax = 5;
    const int _foodMax = 5;
    
    std::string _avatar;
protected:
    PetInfo() = default;
    ~PetInfo() = default;
    
public:

    const std::string& GetAvatar() const { return _avatar;};
    void SetAvatar(std::string& avatar);
    
    int GetMaxHappy() const { return _happyMax;};
    int GetHappy() const { return _happy;};
    void SetHappy(int happy);
    
    int GetMaxFood() const { return _foodMax;};
    int GetFood() const { return _food;};
    void SetFood(int food);
    
    int GetYear() const { return _year;};
    void SetYear(int year);
    
    //TODO: add functions Save() Load()
    friend Singleton<PetInfo>;
};
#endif /* PetStats_hpp */
