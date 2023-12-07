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

class Timer
{
    std::chrono::steady_clock::time_point _startTime;
    
    //TODO Add std::chrono::system_clock to represent real clock forPet schedule;
    std::chrono::steady_clock::time_point _lastCallTime;
    
    Signal<int> _onTimeUpdated;
    Signal<> _onTimeUpdatedWithoutParametrs;
    
public:
    Timer();
    
    //Subscribers  _;
   //  Subscribe()
    // Unscribe();
    void PrintTime();
    
    Signal<int>& GetOnTimeUpdatedSignal() {return _onTimeUpdated;};
    Signal<>& GetOnTimeUpdatedSignalWithoutParametrs() {return _onTimeUpdatedWithoutParametrs;};
    
    
};
#endif /* Timer_hpp */
