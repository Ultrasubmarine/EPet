//
//  Time.cpp
//  EPet
//
//  Created by marina porkhunova on 10.01.2026.
//

#include "Time.hpp"

#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "Logging.hpp"

void Time::Init()
{
    _session = 0.0;
    _clock = std::make_unique<SystemClockSource>();
}

void Time::Update(double dt)
{
    if( dt < 0.0) {
        dt = 0.0;
    }
    
    _session += dt; // seconds
    _clock->Update(dt);
}

std::string Time::GetClockTimeString() const {
    std::int64_t ms = _clock->GetNow();
    std::time_t t = ms / 1000;
    std::tm tm{};
#if defined(_WIN32)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%H:%M:%S");
    //oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

