//
//  IStateSystem.cpp
//  EPet
//
//  Created by marina porkhunova on 11.08.2026.
//

#include "StateTicker.hpp"
#include "Logging.hpp"

#include "Time.hpp"
#include "Game.hpp"

#include "TimeComponents.hpp"
#include "CommonComponents.hpp"
#include "HM_StatesComponents.hpp"


void StateTicker ::RecalculateParametrs(std::time_t lastUpdate)
{
    //Recalculate current parametrs that was save long time ago
    if(lastUpdate) {
        const auto now = Time::Instance().GetClockTime();
        auto duration = GetDuration();

        while(IsPossibleToChange() && duration > 0 && lastUpdate + duration <= now) {
            lastUpdate += duration;
            OnTimerEndedInOutOffGame(lastUpdate);

            duration = GetDuration(); // maybe changed
        }
    }
}

void StateTicker::OnTimerEndedInOutOffGame(const std::time_t& updateTime)
{
    OnTimerEndedInGame(updateTime);
}

entt::entity StateTicker::CreateNextTimer(std::time_t& lastUpdate)
{
    if(IsPossibleToChange())
    {
        auto timeThatAlreadyGone = Time::Instance().GetClockTime() - lastUpdate;
        auto neededDuration = GetDuration() - timeThatAlreadyGone;
        if(neededDuration < 0)
        {
            LOG_ERROR("IStateSystem::CreateNextTimer() calculated duration for timer <0. RecalculateParametrs() doesn't cover all timeline");
            neededDuration = GetDuration();
        }
        
        entt::entity entity;
        if(CreateTimer(neededDuration, &entity))
        {
            return entity;
        }
    }
    return entt::null;
}
