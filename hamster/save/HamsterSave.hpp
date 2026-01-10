//
//  HamsterSave.hpp
//  EPet
//
//  Created by marina porkhunova on 19.11.2025.
//

#ifndef HamsterSave_hpp
#define HamsterSave_hpp

#include <stdio.h>
#include "PlayerSave.hpp"

struct HamsterPlayerInfo: public IPlayerInfo
{
    // hamster states
    uint lifeTime = 0; // duration  TODO: in what? seconds? 1 day = 86400 sec. maybe bad if it will be 16bit system
    int level = 0;
    
    int happyState = 0;
    int foodState = 0;
  
public:
    HamsterPlayerInfo();
    
    void Save(json& data) override;
    void Load(const json& data) override;
    
    void SetDefaultValues() override;
};
#endif /* HamsterSave_hpp */
