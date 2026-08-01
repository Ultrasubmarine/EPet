//
//  GrowingSystem.hpp
//  EPet
//
//  Created by marina porkhunova on 18.07.2026.
//

#ifndef GrowingSystem_hpp
#define GrowingSystem_hpp

#include <ctime>

#include "ISystem.hpp"

class PlayerSave;

class GrowingSystem: public ISystem {
    SYSTEM_BODY(GrowingSystem)
    
public:
    void Init() override;
    void DeInit() override {};
    void Update(double dt) override;
    
    PlayerSave* _playerSave;

private:
    void RecalculateParametrs(const int& currentValue, const std::time_t& lastUpdate, int& nextValue, std::time_t& nextUpdate);
    
    std::time_t GetDuration();
    bool IsPossibleToChange();
    
    void ApplyTimerByStartRecalculation(const std::time_t& updateTime); // maybe different
    void ApplyTimerByGameProgress(const std::time_t& updateTime);
    
private:
    int _level = 0; // tmp place 
};

#endif /* GrowingSystem_hpp */
