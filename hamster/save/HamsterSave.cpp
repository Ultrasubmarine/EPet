//
//  HamsterSave.cpp
//  EPet
//
//  Created by marina porkhunova on 19.11.2025.
//

#include "HamsterSave.hpp"
#include "Logging.hpp"

HamsterPlayerInfo::HamsterPlayerInfo()
{
    SetDefaultValues();
}

void HamsterPlayerInfo::Load(const json &data) {

    if(data.is_object())
    {
        lifeTime = data.value("lifeTime", 0);
        level = data.value("level", 0);
        
        happyState = data.value("happyState", 0);
        foodState = data.value("foodState", 0);
        
        LOG_MESSAGE("HamsterPlayerInfo::Load(): Load Player Info from save file");
    }
    else {
        SetDefaultValues();
        LOG_MESSAGE("HamsterPlayerInfo::Load(): Load Player Info from default values");
    }
}

void HamsterPlayerInfo::Save(json &data) {
    
    data["lifeTime"] = lifeTime;
    data["level"] = level;
    
    data["happyState"] = happyState;
    data["foodState"]  = foodState;
}

void HamsterPlayerInfo::SetDefaultValues() {
    lifeTime = 0;
    level = 0;
    
    happyState = 0;
    foodState = 0;
}
