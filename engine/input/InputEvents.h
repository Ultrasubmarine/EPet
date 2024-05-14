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

struct KeyEventInfo
{
    InputKey Key;
    KeyState State;
    time_point Time;
};

struct VirtualKeyEvent
{
    std::string Name;
    KeyState State;
};
//TODO: mouse events. window events

#endif /* InputEvents_h */