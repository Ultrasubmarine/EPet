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
#include "StateTicker.hpp"

class PlayerSave;
struct Level;

class GrowingSystem: public ISystem, private StateTicker {
    SYSTEM_BODY(GrowingSystem)
    
public:
    void Init() override;
    void DeInit() override {};
    void Update(double dt) override;
    
    PlayerSave* _playerSave;

private:
    
    Level* Load();
    virtual void OnTimerEndedInGame(const std::time_t& updateTime) override;
    
    void DeleteOneFrameComponent();
};

#endif /* GrowingSystem_hpp */
