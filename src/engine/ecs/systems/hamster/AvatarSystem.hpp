//
//  SavingSystem.hpp
//  EPet
//
//  Created by marina porkhunova on 23.09.2026.
//

#ifndef AvatarSystem_hpp
#define AvatarSystem_hpp

#include "ISystem.hpp"

class PlayerSave;

class AvatarSystem: public ISystem {
    SYSTEM_BODY(AvatarSystem)
    
public:
    void Init() override;
    void Update(double dt) override;
    
    bool UpdateAvatar();
    std::string RecalculateTag();
};

#endif // !AvatarSystem_hpp
