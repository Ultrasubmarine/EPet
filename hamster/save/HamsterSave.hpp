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
    int lifeTime;
    int level;
    
    int happyState;
    int foodState;
  
public:
    void Save(json& data) override {};
    void Load(const json& data) override{};
    
    void SetDefault() override {};
};
#endif /* HamsterSave_hpp */
