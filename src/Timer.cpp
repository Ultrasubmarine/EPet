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
    _lastCallTime = _startTime;
}

void Timer::Update()
{
    auto currentTime =std::chrono::steady_clock::now();
    std::chrono::duration<double> dt= std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - _lastCallTime);
    _lastCallTime = currentTime;
    
    _onTimeUpdated.Broadcast(dt.count());
}

void Timer::PrintTime()
{
    std::chrono::duration<double> time = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - _startTime);
    std::cout<<std::endl<<"time: "<<time.count()<<std::endl;
}
