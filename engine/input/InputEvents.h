//
//  InputEvents.h
//  EPet
//
//  Created by marina porkhunova on 03.05.2024.
//

#ifndef InputEvents_h
#define InputEvents_h

#include "EngineSettings.h"

enum KeyState
{
    Pressed,
    Released
};

struct KeyEvent
{
    InputKey Key;
    KeyState State;
};

//TODO: mouse events. window events

#endif /* InputEvents_h */
