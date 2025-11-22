//
//  HamsterSave.cpp
//  EPet
//
//  Created by marina porkhunova on 19.11.2025.
//

#include "HamsterSave.hpp"

void HamsterPlayerInfo::Load(const json &data) {

    lifeTime = data.value("lifeTime", 0);
    level = data.value("level", 0);
    
    happyState = data.value("happyState", 0);
    foodState = data.value("foodState", 0);
}

void HamsterPlayerInfo::Save(json &data) {
    
    data["lifeTime"] = lifeTime;
    data["level"] = level;
    
    data["happyState"] = happyState;
    data["foodState"]  = foodState;
}

