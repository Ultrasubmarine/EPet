//
//  GrowingSystem.cpp
//  EPet
//
//  Created by marina porkhunova on 18.07.2026.
//

#include "GrowingSystem.hpp"

#include <cmath>

#include "TimeComponents.hpp"
#include "CommonComponents.hpp"
#include "HM_StatesComponents.hpp"

#include "Time.hpp"
#include "Game.hpp"
#include "PlayerSave.hpp"
#include "Logging.hpp"

SYSTEM_CPP(GrowingSystem);

Level* GrowingSystem::Load()
{
    _playerSave = Game::Instance().GetPlayerSave();
    if(!_playerSave || !_playerSave->GetData())
    {
        // TODO think about errors. maybe optimize it. some how
        LOG_ERROR("GrowingSystem::LoadAge() saveData doesn't exist. Loading hamster level skipped");
        return nullptr;
    }
    
    int lastAge = 0;
    std::time_t lastUpdate = 0;
    if(!GetAttribute(_playerSave->GetData(), "level", lastAge, lastUpdate))
    {
        // NEW PLAYER. DOESN'T HAVE A "Level" IN DATA
        _registry.emplace<Empty_Level_OF>(_registry.create());
    }
    
    // for test
    // ApplyTimerByStartRecalculation(Time::Instance().GetClockTime());
    
    auto& level = _registry.emplace<Level>(_registry.create(), lastAge, lastUpdate);
    return &level;
}


void GrowingSystem::Init()
{
    auto level = Load();
    if(!level) {
        return;
    }

    // update hamster level for current time
    RecalculateParametrs(level->lastUpdate);
    
    // create new timer
    auto entity = CreateNextTimer(level->lastUpdate);
    _registry.emplace<LevelTimer>(entity);
    
    
//    if(IsPossibleToChange())
//    {
//        auto timeThatAlreadyGone = Time::Instance().GetClockTime() - level->lastUpdate;
//        auto neededDuration = GetDuration() - timeThatAlreadyGone;
//        if(neededDuration < 0)
//        {
//            LOG_ERROR("GrowingSystem::Init() calculated duration for timer <0. RecalculateParametrs() doesn't cover all timeline");
//            neededDuration = GetDuration();
//        }
//        
//        entt::entity entity;
//        if(CreateTimer(10.0, &entity))//CreateTimer(neededDuration, &entity))
//        {
//            //code only for growing system
//            _registry.emplace<LevelTimer>(entity);
//            
//            
//            _registry.emplace<Text>(entity);
//            _registry.emplace<SetNewFont>(entity, DEFAULT_FONT);
//            
//            _registry.emplace<RendererObject>(entity);
//            _registry.emplace<Sorting>(entity, 1000);
//            _registry.emplace<Transform>(entity, IPoint(150, 150));
//        }
//    }
}

void GrowingSystem::RecalculateParametrs(std::time_t lastUpdate)
{
    //Recalculate current parametrs that was save long time ago
    if(lastUpdate) {
        const auto now = Time::Instance().GetClockTime();
        auto duration = GetDuration();

        while(IsPossibleToChange() && duration > 0 && lastUpdate + duration <= now) {
            lastUpdate += duration;
            ApplyTimerByStartRecalculation(lastUpdate);

            duration = GetDuration(); // maybe changed
        }
    }
}

void GrowingSystem::ApplyTimerByStartRecalculation(const std::time_t& updateTime)
{
    ApplyTimerByGameProgress(updateTime); // maybe different but now it's the same
}

void GrowingSystem::ApplyTimerByGameProgress(const std::time_t& updateTime)
{
    int valueForSave = 0;
    for(auto [ent, level] : _registry.view<Level>().each())
    {
        valueForSave = ++level.value;
        level.lastUpdate = updateTime;
  
        _registry.emplace_or_replace<LevelChanged_OF>(ent);
    }
    
    // tmp place for save
    SetAttribute(_playerSave->GetData(), "level", valueForSave, updateTime);
    _playerSave->Save();
}

void GrowingSystem::Update(double dt){

    // delete all one frame components
    _registry.clear<LevelChanged_OF>();
    for(auto entity : _registry.view<Empty_Level_OF>()) {
        _registry.destroy(entity);
    }
    //--------------------------------
    
    
    for(auto [ent, timer] : _registry.view<Timer, TimerFinished_OF, LevelTimer>().each())
    {
        //Apply changes
        auto now = Time::Instance().GetClockTime();
        ApplyTimerByGameProgress(now);
        
        //Mark
        _registry.emplace_or_replace<UnusedTimer>(ent);
        
        //CreateNextTimer
        auto entity = CreateNextTimer(now);
        _registry.emplace<LevelTimer>(entity);
    }
};

entt::entity GrowingSystem::CreateNextTimer(std::time_t& lastUpdate)
{
    // create new timer
    if(IsPossibleToChange())
    {
        auto timeThatAlreadyGone = Time::Instance().GetClockTime() - lastUpdate;
        auto neededDuration = GetDuration() - timeThatAlreadyGone;
        if(neededDuration < 0)
        {
            LOG_ERROR("GrowingSystem::CreateNextTimer() calculated duration for timer <0. RecalculateParametrs() doesn't cover all timeline");
            neededDuration = GetDuration();
        }
        
        entt::entity entity;
        if(CreateTimer(neededDuration, &entity))
        {
            // _registry.emplace<LevelTimer>(entity);
            _registry.emplace<Text>(entity);
            _registry.emplace<SetNewFont>(entity, DEFAULT_FONT);

            _registry.emplace<RendererObject>(entity);
            _registry.emplace<Sorting>(entity, 1000);
            _registry.emplace<Transform>(entity, IPoint(150, 150));
            return entity;
        }
    }
    return entt::null;
}




