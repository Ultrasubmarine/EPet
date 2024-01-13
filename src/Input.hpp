//
//  Input.hpp
//  EPet
//
//  Created by marina porkhunova on 12.01.2024.
//

#ifndef Input_hpp
#define Input_hpp

#include <stdio.h>
#include <queue>
#include <mutex>

class Input
{
    std::mutex inputMutex;
    std::queue<char> events;
    
public:
    void AddEvent(char c);
    char GetEvent(); // return -1 if empty;
};

/// make extra thread for catching events.
/// return - object wich is registring all events;
//Input* InitInput();


#endif /* Input_hpp */
