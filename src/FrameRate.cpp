//
//  FrameRate.cpp
//  EPet
//
//  Created by marina porkhunova on 17.12.2023.
//

#include "FrameRate.hpp"
#include <thread>

void FrameRate::FirstInitialization()
{
    _delta = std::chrono::nanoseconds::zero();
    _nowClock = std::chrono::steady_clock::now();
    
    _fixedDelta = std::chrono::seconds(1);
    _fixedDelta /= _fps;
}

void FrameRate::SetFixedFrame(int fps)
{
    _fixedFrameRate = true;
    
    _fixedDelta = std::chrono::seconds(1);
    _fixedDelta /= fps;
    _fps = fps;
}

void FrameRate::WaitFrame()
{
    _lastClock = _nowClock;
    _nowClock = std::chrono::steady_clock::now();
    
    _delta = _nowClock - _lastClock;
    
        
    if(_fixedFrameRate)
    {
        auto wait = _fixedDelta - _delta;
        _delta += wait;
        
        if(wait > std::chrono::nanoseconds::zero())
        {
            std::this_thread::sleep_for(wait);
        }
    }
  
    _lastClock = std::chrono::steady_clock::now();
}

float FrameRate::GetDeltaTime()
{
    return _delta.count()/ static_cast<float>(std::nano::den);
}

float FrameRate::GetFixedDeltaTime()
{
    return _fixedDelta.count()/ static_cast<float>(std::nano::den);
}
