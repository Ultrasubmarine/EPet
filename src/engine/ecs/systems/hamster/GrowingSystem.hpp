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
#include "HM_StatesComponents.hpp"

class GrowingSystem: public ISystem, private StateTicker<LevelTimer> {
    SYSTEM_BODY(GrowingSystem, StateTicker<LevelTimer>(registry))
    
public:
    void Init() override;
    void DeInit() override {};
    void Update(double dt) override;

private:
    
    bool Load(); // true if success 
    
    virtual void ApplyStep(std::time_t updateTime) override;
    virtual std::time_t GetLastUpdate() const override;
    virtual std::time_t GetDuration() const override;
    
    void DeleteOneFrameComponent();
};

#endif /* GrowingSystem_hpp */
