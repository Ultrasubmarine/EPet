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

#include "Subscription.hpp"

//TODO: Add std::chrono::system_clock to represent real clock forPet schedule;
class Timer
{
    std::chrono::steady_clock::time_point _startTime;
    std::chrono::steady_clock::time_point _lastCallTime;
    
    Signal<double> _onTimeUpdated;
    
public:
    Timer();
    
    void Update();
    void PrintTime();
    
    Signal<double>& GetOnTimeUpdatedSignal() {return _onTimeUpdated;};
    
    
};
#endif /* Timer_hpp */
