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
struct LevelTimer;

class GrowingSystem: public ISystem, private StateTicker<LevelTimer> {
    SYSTEM_BODY(GrowingSystem, StateTicker<LevelTimer>(registry))
    
public:
    void Init() override;
    void DeInit() override {};
    void Update(double dt) override;
    
    PlayerSave* _playerSave;

private:
    
    Level* Load();
    
    virtual void ApplyStep(std::time_t updateTime) override;
    virtual const std::time_t GetLastUpdate() override;
    virtual const std::time_t GetDuration() override;
    
    void DeleteOneFrameComponent();
};

#endif /* GrowingSystem_hpp */
