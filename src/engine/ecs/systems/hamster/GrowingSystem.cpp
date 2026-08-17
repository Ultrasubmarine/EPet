//
//  GrowingSystem.cpp
//  EPet
//
//  Created by marina porkhunova on 18.07.2026.
//

#include "GrowingSystem.hpp"

#include "HM_StatesComponents.hpp"

#include "Time.hpp"
#include "Game.hpp"
#include "PlayerSave.hpp"
#include "Logging.hpp"

SYSTEM_CPP(GrowingSystem);

bool GrowingSystem::Load()
{
    // need to move it?
    auto playerSave = Game::Instance().GetPlayerSave();
    if(!playerSave || !playerSave->GetData())
    {
        // TODO think about errors. maybe optimize it. some how
        LOG_ERROR("GrowingSystem::LoadAge() saveData doesn't exist. Loading hamster level skipped");
        return false;
    }

    int lastAge = 0;
    std::time_t lastUpdate = Time::Instance().GetClockTime();
    if(!GetAttribute(playerSave->GetData(), "level", lastAge, lastUpdate))
    {
        // NEW PLAYER. DOESN'T HAVE A "Level" IN DATA
        _registry.emplace<Empty_Level_OF>(_registry.create());
    }
    
    _registry.emplace<Level>(_registry.create(), lastAge, lastUpdate);
    return true;
}


void GrowingSystem::Init()
{
    if(!Load()) {
        return;
    }

    InitState();
}

void GrowingSystem::ApplyStep(const std::time_t updateTime)
{
    for(auto [ent, level] : _registry.view<Level>().each())
    {
        level.value++;
        level.lastUpdate = updateTime;
  
        _registry.emplace_or_replace<LevelChanged_OF>(ent);
    }
}

std::time_t GrowingSystem::GetLastUpdate() const
{
    for(auto [ent, level] :_registry.view<Level>().each())
    {
        return level.lastUpdate;
    }
    return 0;
}

std::time_t GrowingSystem::GetDuration() const
{
    return 60 * 1;
}

void GrowingSystem::Update(double dt){

    DeleteOneFrameComponent();
    
    UpdateState();
}

void GrowingSystem::DeleteOneFrameComponent()
{
    _registry.clear<LevelChanged_OF>();
    for(auto entity : _registry.view<Empty_Level_OF>()) {
        _registry.destroy(entity);
    }
}




