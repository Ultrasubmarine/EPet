//
//  Timer.hpp
//  EPet
//
//  Created by marina porkhunova on 30.11.2023.
//

#ifndef Timer_hpp
#define Timer_hpp

#include <stdio.h>
#include <chrono>

class Timer
{
    std::chrono::steady_clock::time_point _startTime;
    //TODO Add std::chrono::system_clock to represent real clock forPet schedule;
public:
    Timer();
    
    void PrintTime();    
};
#endif /* Timer_hpp */
