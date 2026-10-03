//
//  TimerSystem.hpp
//  EPet
//
//  Created by marina porkhunova on 19.01.2025.
//

#ifndef TimerSystem_hpp
#define TimerSystem_hpp

#include "ISystem.hpp"

class TimerSystem: public ISystem {
    SYSTEM_BODY(TimerSystem)
    
public:
    void Init() override;
    void DeInit() override {};
    void Update(double dt) override;
};

#endif /* TimerSystem_hpp */
