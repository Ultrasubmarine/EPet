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
    
    virtual void ApplyTimerByStartRecalculation(const std::time_t& updateTime); // maybe different
    virtual void ApplyTimerByGameProgress(const std::time_t& updateTime);
    // ______________________________
    
    entt::entity CreateNextTimer(std::time_t& lastUpdate);
};

#endif /* GrowingSystem_hpp */
