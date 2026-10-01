//
//  FrameRate.cpp
//  EPet
//
//  Created by marina porkhunova on 17.12.2023.
//

#include "FrameRate.hpp"
#include "Logging.hpp"

#include <thread>

void FrameRate::FirstInitialization()
{
    _fixedDelta = std::chrono::seconds(1);
    _fixedDelta /= _fps;

    _delta = _fixedDelta; // first frame has no previous one: report expected frame time, not 0
    _lastClock = std::chrono::steady_clock::now();
}

void FrameRate::SetFixedFrame(int fps)
{
    _fixedFrameRate = true;
    
    _fixedDelta = std::chrono::seconds(1);
    _fixedDelta /= fps;
    _fps = fps;
    LOG_MESSAGE("set fps="<<fps);
}

void FrameRate::WaitFrame()
{
    auto now = std::chrono::steady_clock::now();

    if(_fixedFrameRate)
    {
        auto wait = _fixedDelta - (now - _lastClock);

        if(wait > std::chrono::nanoseconds::zero())
        {
            std::this_thread::sleep_for(wait);
        }
    }

    auto end = std::chrono::steady_clock::now();
    _delta = end - _lastClock; // actual frame time, including the sleep
    _lastClock = end;
}

float FrameRate::GetDeltaTime()
{
    return _delta.count()/ static_cast<float>(std::nano::den);
}

float FrameRate::GetFixedDeltaTime()
{
    return _fixedDelta.count()/ static_cast<float>(std::nano::den);
}
