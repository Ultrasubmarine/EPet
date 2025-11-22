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
    int lifeTime = 0;
    int level = 0;
    
    int happyState = 0;
    int foodState = 0;
  
public:
    void Save(json& data) override;
    void Load(const json& data) override;
};
#endif /* HamsterSave_hpp */
