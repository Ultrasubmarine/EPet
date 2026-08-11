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


/// USE IN
///void YOUR_SYSTEM_NAME:Init()
/// {   ... other code...
///
///     RecalculateParametrs(state->lastUpdate); //  for update parametrs after loading game
///
///     auto entity = CreateNextTimer(level->lastUpdate); // for creating new timer for next updates
///     _registry.emplace<YOUR_STATE_NAME_Timer>(entity); // to marl your timer loke spechial state to control
///
/// ... other code...
/// }

class StateTicker {
protected:
    
    void RecalculateParametrs(std::time_t lastUpdate);
    
    virtual std::time_t GetDuration() { return std::time_t(1.0 /* minutes */ * 60); }; // in seconds
    virtual bool IsPossibleToChange() { return true; };
    
    virtual void OnTimerEndedInOutOffGame(const std::time_t& updateTime); // defalult: call ApplyTimerByGameProgress(...)
    virtual void OnTimerEndedInGame(const std::time_t& updateTime) = 0;

    entt::entity CreateNextTimer(std::time_t& lastUpdate);
};

#endif /* IStateSystem_hpp */
