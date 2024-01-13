//
//  Input.cpp
//  EPet
//
//  Created by marina porkhunova on 12.01.2024.
//

#include "Input.hpp"
#include <thread>

void Input::AddEvent(char c)
{
    inputMutex.lock();
    events.push(c);
    inputMutex.unlock();
}

char Input::GetEvent()
{
    if(events.empty())
    {
        return -1;
    }
    
    inputMutex.lock();
    auto e = events.front();
    events.pop();
    inputMutex.unlock();
    return e;
}

