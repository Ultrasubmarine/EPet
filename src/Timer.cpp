//
//  Timer.cpp
//  EPet
//
//  Created by marina porkhunova on 30.11.2023.
//

#include "Timer.hpp"
#include <iostream>

Timer::Timer()
{
    _startTime = std::chrono::steady_clock::now();
}


void Timer::PrintTime()
{
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - _startTime);
    std::cout<<std::endl<<"time has passed: "<<time_span.count()<<std::endl;
    
    _onTimeUpdated.Broadcast();
}
