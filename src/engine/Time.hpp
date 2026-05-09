//
//  Time.hpp
//  EPet
//
//  Created by marina porkhunova on 10.01.2026.
//

#ifndef Time_hpp
#define Time_hpp

#include <chrono>
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
    virtual std::int64_t GetNow() const = 0; // in milliseconds
};


class Time final: public Singleton<Time>
{
public:
    
    void Init();
    void Update(double dt);
    
    // session
    double GetSessionDuration() const { return _session;}

    // clock
    std::int64_t GetClockTime() const { return _clock->GetNow();}
    std::string GetClockTimeString() const;

private:
    double _session = 0.0; // in milliseconds
    std::unique_ptr<IClockSource> _clock; // default == SystemClockSource
 // TODO: Timers?
};


// 1 type of clock. system
struct SystemClockSource : IClockSource {
    void Update(double) override {} // nothing to do
    std::int64_t GetNow() const override {
        const auto now = std::chrono::system_clock::now().time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
    }
};

// 2 type of clock. custom, increasing in update()
struct AccumulatedClockSource : IClockSource {
    std::int64_t _unixTime = 0; // текущее «виртуальное» реальное время
    void Init() override { /* опционально: _unixMs = seed */ }
    void Update(double dtMs) override {
        if (dtMs < 0) dtMs = 0;
        // можно клампить слишком большие шаги
        _unixTime += static_cast<std::int64_t>(dtMs);
    }
    // TODO: set clock
    std::int64_t GetNow() const override { return _unixTime; }
};

#endif /* Time_hpp */
