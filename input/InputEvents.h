//
//  InputEvents.h
//  EPet
//
//  Created by marina porkhunova on 03.05.2024.
//

#ifndef InputEvents_h
#define InputEvents_h

enum KeyState
{
    Pressed,
    Released
};

struct KeyEvent
{
    std::string name;
    KeyState state;
};


#endif /* InputEvents_h */
