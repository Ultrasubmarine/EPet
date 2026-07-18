//
//  GrowingSystem.hpp
//  EPet
//
//  Created by marina porkhunova on 18.07.2026.
//

#ifndef GrowingSystem_hpp
#define GrowingSystem_hpp

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
    void LoadAge(int& value, std::time_t& lastUpdate);
};

#endif /* GrowingSystem_hpp */
