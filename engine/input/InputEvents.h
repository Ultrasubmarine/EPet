//
//  InputEvents.h
//  EPet
//
//  Created by marina porkhunova on 03.05.2024.
//

#ifndef InputEvents_h
#define InputEvents_h

#include "EngineSettings.h"

using time_point = std::chrono::steady_clock::time_point;

enum KeyState
{
    Pressed,
    Released
};

struct KeyEvent
{
    std::string Name;
    KeyState State;
};

#endif /* InputEvents_h */
