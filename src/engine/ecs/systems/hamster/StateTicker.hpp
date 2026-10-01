//
//  StateTicker.hpp
//  EPet
//
//  Created by marina porkhunova on 11.08.2026.
//

#ifndef StateTicker_hpp
#define StateTicker_hpp

#include <ctime>

#include "registry.hpp"

#include "Logging.hpp"

#include "Time.hpp"
#include "TimeComponents.hpp"

template<class TTimerTag>
class StateTicker {
    
protected:
    StateTicker(entt::registry& registry) : _reg(registry){};
    ~StateTicker() = default;
    
    /// call in Init() and Update()  in inheritor class
    void InitState();
    void UpdateState();
    ///______________________________
    
    void RecalculateParameter();
    
    /// 0 means "state has no history yet"
    virtual std::time_t GetLastUpdate() const = 0;
    virtual std::time_t GetDuration() const = 0; // in seconds
    virtual bool IsPossibleToChange() const { return true; };
    
    virtual void ApplyStep(std::time_t updateTime) = 0;
    virtual void ApplyOfflineStep(std::time_t updateTime) { ApplyStep(updateTime); };

private:
    entt::entity StartTimer();
    
private:
    entt::registry& _reg;
};


template<class TTimerTag>
void StateTicker<TTimerTag>::InitState()
{
    RecalculateParameter();
    StartTimer();
}

template<class TTimerTag>
void StateTicker<TTimerTag>::UpdateState()
{
    for(auto [ent, timer] : _reg.view<Timer, TimerFinished_OF, TTimerTag>().each())
    {
        //Apply changes
        auto now = Time::Instance().GetClockTime();
        ApplyStep(now);
        
        //Mark
        _reg.emplace_or_replace<UnusedTimer>(ent);
        
        //CreateNextTimer
        StartTimer();
    }
    
    // timer doesn't exist. smth blocked it.
    // try to start timer again
    if (_reg.view<Timer, TTimerTag>().front() == entt::null)
    {
        StartTimer();
    }
}

template<class TTimerTag>
void StateTicker<TTimerTag>::RecalculateParameter()
{
    auto lastUpdate = GetLastUpdate();
    
    //Recalculate current parametrs that was saved long time ago
    if(lastUpdate) {
        const auto now = Time::Instance().GetClockTime();
        auto duration = GetDuration();

        while(IsPossibleToChange() && duration > 0 && lastUpdate + duration <= now) {
            lastUpdate += duration;
            ApplyOfflineStep(lastUpdate);

            duration = GetDuration(); // maybe changed
        }
    }
}

template<class TTimerTag>
entt::entity StateTicker<TTimerTag>::StartTimer()
{
    auto lastUpdate = GetLastUpdate();
    
    if(IsPossibleToChange())
    {
        auto timeThatAlreadyGone = lastUpdate == 0 ? 0 : Time::Instance().GetClockTime() - lastUpdate;
        if (timeThatAlreadyGone < 0) {
            LOG_MESSAGE("lastUpdate is in the future. Clock was probably changed.");
            timeThatAlreadyGone = 0;
        }
        
        auto neededDuration = GetDuration() - timeThatAlreadyGone;
        if(neededDuration < 0) {
            LOG_ERROR("Сalculated duration for timer <0. RecalculateParametrs() doesn't cover all timeline");
            neededDuration = GetDuration();
        }

        entt::entity ent = entt::null;
        if (CreateTimer(neededDuration, &ent) && ent != entt::null) {
           _reg.emplace<TTimerTag>(ent);
            return ent;
        }
        else {
            LOG_ERROR("Error with creating timer.");
        }
    }
    // no log for blocked state: UpdateState() retries every frame
    return entt::null;
}

#endif /* StateTicker_hpp */
