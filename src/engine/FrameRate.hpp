//
//  FrameRate.hpp
//  EPet
//
//  Created by marina porkhunova on 17.12.2023.
//

#ifndef FrameRate_hpp
#define FrameRate_hpp

#include <stdio.h>
#include <chrono>

#define DEFAULT_FPS 60

class FrameRate
{
    bool _fixedFrameRate = false;
    int _fps;
    
    std::chrono::nanoseconds _delta;
    std::chrono::nanoseconds _fixedDelta;
    
    std::chrono::time_point<std::chrono::steady_clock> _lastClock, _nowClock;
    
public:
    void FirstInitialization();
    void SetFixedFrame(int fps);
    void WaitFrame();
    
    float GetDeltaTime(); /// in milliseconds
    float GetFixedDeltaTime();
    
    FrameRate() :_fps(DEFAULT_FPS){};
};
#endif /* FrameRate_hpp */
