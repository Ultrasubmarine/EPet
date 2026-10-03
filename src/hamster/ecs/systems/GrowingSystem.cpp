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
#include "Logger.hpp"

SYSTEM_CPP(GrowingSystem);

bool GrowingSystem::Load()
{
    // need to move it?
    auto playerSave = Game::Instance().GetPlayerSave();
    if(!playerSave || !playerSave->GetData())
    {
        // TODO think about errors. maybe optimize it. some how
        LOG_ERROR("saveData doesn't exist. Loading hamster level skipped");
        return false;
    }

    int lastAge = 0;
    std::time_t lastUpdate = Time::Instance().GetClockTime();
    auto levelEntity = _registry.create();
    
    if(!GetAttribute(playerSave->GetData(), "level", lastAge, lastUpdate))
    {
        // NEW PLAYER. DOESN'T HAVE A "Level" IN DATA
        _registry.emplace<Empty_Level_OF>(levelEntity);
    }
    
    _registry.emplace<Level>(levelEntity, lastAge, lastUpdate);
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
    return 60 * 60 * 9; // 9 hours 
}

void GrowingSystem::Update(double dt){

    DeleteOneFrameComponent();
    
    UpdateState();
}

void GrowingSystem::DeleteOneFrameComponent()
{
    _registry.clear<LevelChanged_OF>();
    _registry.clear<Empty_Level_OF>();
}




