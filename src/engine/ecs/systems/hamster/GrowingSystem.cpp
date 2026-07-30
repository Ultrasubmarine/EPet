//
//  GrowingSystem.cpp
//  EPet
//
//  Created by marina porkhunova on 18.07.2026.
//

#include "GrowingSystem.hpp"

#include "TimeComponents.hpp"
#include "CommonComponents.hpp"

#include "Time.hpp"
#include "Game.hpp"
#include "PlayerSave.hpp"
#include "Logging.hpp"

SYSTEM_CPP(GrowingSystem);


void GrowingSystem::Init()
{
    _playerSave = Game::Instance().GetPlayerSave();
    if(!_playerSave || !_playerSave->GetData())
    {
        // TODO think about errors. maybe optimize it. some how
        LOG_ERROR("GrowingSystem::LoadAge() saveData doesn't exist. Loading hamster level skipped");
        return;
    }
    
   // ApplyTimerByStartRecalculation(Time::Instance().GetClockTime());
    
    // load
    int lastAge = 0;
    std::time_t lastUpdate = 0;
    if(!GetAttribute(_playerSave->GetData(), "level", lastAge, lastUpdate))
    {
        // new player
        // do smth?
    }
    _level = lastAge; // tmp
    
    //Recalculate current parametrs
    if(lastUpdate)
    {
        auto duration = static_cast<std::time_t>(std::round(GetDuration()));
        while(IsPossibleToChange() && lastUpdate + duration <= Time::Instance().GetClockTime())
        {
            lastUpdate += duration;
            ApplyTimerByStartRecalculation(lastUpdate);

            duration = GetDuration(); // maybe changed
        }
    }
    
    if(IsPossibleToChange() && lastUpdate > Time::Instance().GetClockTime())
    {
        // create new timer for next update;
    }
    
    
    // Recalculate timer for next update
    
    std::time_t nextUpdate = 0;
   // RecalculateParametrs(age, lastUpdate, nextAge, nextUpdate);
    if(nextUpdate == 0)
    {
        // no more changes
        return;
    }
    
    
    // Create timer
    // ...
    
    
    // WHEN Save?
//    (*saveData)["level"] = {
//        {"value", age},
//        {"lastUpdate", static_cast<std::int64_t>(std::time(nullptr))}
//    };
    
    
    entt::entity entity;
    if(CreateTimer(10.0, &entity))
    {
        _registry.emplace<Text>(entity);
        _registry.emplace<SetNewFont>(entity, DEFAULT_FONT);
        
        _registry.emplace<RendererObject>(entity);
        _registry.emplace<Sorting>(entity, 1000);
        _registry.emplace<Transform>(entity, IPoint(50, 50));
    }


}

bool GrowingSystem::IsPossibleToChange()
{
    return true;
}

double GrowingSystem::GetDuration() // in seconds
{
    return 5 * 60.0;
}

void GrowingSystem::ApplyTimerByStartRecalculation(const std::time_t& updateTime)
{
    ApplyTimerByGameProgress(updateTime); // maybe different but now it's the same
}

void GrowingSystem::ApplyTimerByGameProgress(const std::time_t& updateTime)
{
    SetAttribute(_playerSave->GetData(), "level", ++_level, updateTime);
    _playerSave->Save();
}

void GrowingSystem::Update(double dt){

    // delete all one frame components
    _registry.clear<TimerFinished_OF>();
    
    
    //update timers
    for( auto [ent, timer] : _registry.view<Timer>(entt::exclude<TimerFinished>).each())
    {
        timer.timeLeft -= dt;
        
        // if completed
        if(timer.timeLeft <= 0.0)
        {
            _registry.emplace<TimerFinished_OF>(ent);
            _registry.emplace<TimerFinished>(ent);
        }
    }
    
    //show timers
    for( auto [ent, timer, text] : _registry.view<Timer, Text>().each())
    {
        _registry.emplace_or_replace<SetNewText>(ent, std::to_string(timer.timeLeft));
    }
};

void GrowingSystem::RecalculateParametrs(const int& currentValue, const std::time_t& lastUpdate, int& nextValue, std::time_t& nextUpdate)
{
    //simplest calculation function for test
    nextValue = currentValue + 1;
    
    
  //  std::duration t =
    if(lastUpdate == 0)
    {
       // use full timer
    }
        

    //
}


