//
//  HM_StatesComponents.hpp
//  EPet
//
//  Created by marina porkhunova on 01.08.2026.
//

#ifndef HM_StatesComponents_hpp
#define HM_StatesComponents_hpp

#include <stdio.h>
#include <iostream>
#include <ctime>

#include "registry.hpp"

struct Level
{
    int value = 0;
    std::time_t lastUpdate = 0;
};

struct LevelChanged_OF /// one shot
{
};

struct Empty_Level_OF // player doesnt have level in save data
{
};

struct LevelTimer // entity contains timer for Level counting
{
};


#endif /* HM_StatesComponents_hpp */
