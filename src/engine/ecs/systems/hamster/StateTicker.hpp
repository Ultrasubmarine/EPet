//
//  IStateSystem.hpp
//  EPet
//
//  Created by marina porkhunova on 11.08.2026.
//

#ifndef IStateSystem_hpp
#define IStateSystem_hpp

#include <stdio.h>
#include <ctime>

#include "registry.hpp"

#include "Logging.hpp"

#include "Time.hpp"
#include "Game.hpp"

#include "TimeComponents.hpp"
#include "CommonComponents.hpp"
#include "HM_StatesComponents.hpp"


template<class TTimerTag>
class StateTicker {
    
protected:
    StateTicker(entt::registry& registry) : _reg(registry){};
    
    /// call in Init() and Update()  in ISystem class
    void InitState();
    void UpdateState();
    ///______________________________
    
    void RecalculateParameter();
    
    virtual const std::time_t GetLastUpdate() = 0;
    virtual const std::time_t GetDuration() = 0; // in seconds
    virtual bool IsPossibleToChange() { return true; };
    
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
        auto timeThatAlreadyGone = Time::Instance().GetClockTime() - lastUpdate;
        auto neededDuration = GetDuration() - timeThatAlreadyGone;
        if(neededDuration < 0) {
            LOG_ERROR("StateTicker<TTimerTag>::StartTimer() Сalculated duration for timer <0. RecalculateParametrs() doesn't cover all timeline");
            neededDuration = GetDuration();
        }
        
        entt::entity ent;
        if (CreateTimer(neededDuration, &ent) && ent != entt::null) {
           _reg.emplace<TTimerTag>(ent);
            return ent;
        }
        else {
            LOG_ERROR("StateTicker<TTimerTag>::StartTimer() Error with creating timer.");
        }
    }
    else{
        LOG_MESSAGE("StateTicker<TTimerTag>::StartTimer() State couldn't change. Creating timer was skipped.");
    }
    return entt::null;
}

#endif /* IStateSystem_hpp */
