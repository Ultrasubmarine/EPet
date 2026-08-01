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
struct Level;

class GrowingSystem: public ISystem {
    SYSTEM_BODY(GrowingSystem)
    
public:
    void Init() override;
    void DeInit() override {};
    void Update(double dt) override;
    
    PlayerSave* _playerSave;

private:
    
    Level* Load();
    
    
    // for moving to other class
    virtual void RecalculateParametrs(std::time_t lastUpdate);
    
    virtual std::time_t GetDuration() {return std::time_t(5.0 * 60);};
    virtual bool IsPossibleToChange() {return true;};
    // ______________________________
    
    void ApplyTimerByStartRecalculation(const std::time_t& updateTime); // maybe different
    void ApplyTimerByGameProgress(const std::time_t& updateTime);
    
private:
    int _level = 0; // tmp place 
};

#endif /* GrowingSystem_hpp */
