//
//  Time.hpp
//  EPet
//
//  Created by marina porkhunova on 10.01.2026.
//

#ifndef Time_hpp
#define Time_hpp

#include <chrono>
#include <ctime>
#include <functional>
#include <unordered_map>
#include <cstdint>
#include <mutex>
#include <string>

#include "Singleton.hpp"

// clock
struct IClockSource {
    virtual ~IClockSource() = default;
    virtual void Init() {}
    virtual void Update(double dt) = 0;
    virtual std::time_t GetNow() const = 0; // unix time, in seconds
};


class Time final: public Singleton<Time>
{
public:
    
    void Init();
    void Update(double dt);
    
    // session
    double GetSessionDuration() const { return _session;} // in seconds

    // clock
    std::time_t GetClockTime() const { return _clock->GetNow();} // unix time, in seconds
    std::string GetClockTimeString() const;

private:
    double _session = 0.0; // in seconds
    std::unique_ptr<IClockSource> _clock; // default == SystemClockSource
 // TODO: Timers?
};


// 1 type of clock. system
struct SystemClockSource : IClockSource {
    void Update(double) override {} // nothing to do
    std::time_t GetNow() const override {
        const auto now = std::chrono::system_clock::now().time_since_epoch();
        return std::chrono::duration_cast<std::chrono::seconds>(now).count();
    }
};

// 2 type of clock. custom, increasing in update()
struct AccumulatedClockSource : IClockSource {
    double _unixTime = 0.0; // текущее «виртуальное» реальное время, in seconds
    void Init() override { /* опционально: _unixTime = seed */ }
    void Update(double dt) override {
        if (dt < 0) dt = 0;
        // можно клампить слишком большие шаги
        _unixTime += dt;
    }
    // TODO: set clock
    std::time_t GetNow() const override { return static_cast<std::time_t>(_unixTime); }
};

#endif /* Time_hpp */
