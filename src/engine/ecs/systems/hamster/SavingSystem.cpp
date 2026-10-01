//
//  SavingSystem.cpp
//  EPet
//
//  Created by marina porkhunova on 2.08.2026.
//

#include "SavingSystem.hpp"

#include "HM_StatesComponents.hpp"

#include "Game.hpp"
#include "PlayerSave.hpp"
#include "Logging.hpp"

SYSTEM_CPP(SavingSystem);

void SavingSystem::Init()
{
    _playerSave = Game::Instance().GetPlayerSave();
    if(!_playerSave || !_playerSave->GetData())
    {
        // TODO think about errors. maybe optimize it. some how
        LOG_ERROR("saveData doesn't exist.");
        return;
    }
    
    // because other system in init could update their states
    SaveChangedStates();
}

void SavingSystem::Update(double dt)
{
    SaveChangedStates();
}

void SavingSystem::SaveChangedStates()
{
    if(!_playerSave || !_playerSave->GetData()) {
        return;
    }
    
    bool dirty = false;
    for(auto [ent, level] : _registry.view<Level, LevelChanged_OF>().each())
    {
        SetAttribute(_playerSave->GetData(), "level", level.value, level.lastUpdate);
        dirty = true;
    }
    for(auto [ent, level] : _registry.view<Level, Empty_Level_OF>().each())
    {
        SetAttribute(_playerSave->GetData(), "level", level.value, level.lastUpdate);
        dirty = true;
    }
    
    if(dirty && !_playerSave->Save()) {
        LOG_ERROR("failed to write save file");
    }
}




