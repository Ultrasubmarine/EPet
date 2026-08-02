//
//  SavingSystem.hpp
//  EPet
//
//  Created by marina porkhunova on 2.08.2026.
//

#ifndef SavingSystem_hpp
#define SavingSystem_hpp

#include <ctime>

#include "ISystem.hpp"

class PlayerSave;

class SavingSystem: public ISystem {
    SYSTEM_BODY(SavingSystem)
    
public:
    void Init() override;
    void Update(double dt) override;
    
    PlayerSave* _playerSave;
};

#endif // !SavingSystem_hpp
