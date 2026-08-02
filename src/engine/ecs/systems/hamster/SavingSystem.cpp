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
        LOG_ERROR("SavingSystem::Init() saveData doesn't exist.");
        return;
    }
}

void SavingSystem::Update(double dt)
{
    if(!_playerSave || !_playerSave->GetData()) {
        return;
    }
    
    for(auto [ent, level] : _registry.view<Level, LevelChanged_OF>().each())
    {
        SetAttribute(_playerSave->GetData(), "level", level.value, level.lastUpdate);
        _playerSave->Save();
    }
};





