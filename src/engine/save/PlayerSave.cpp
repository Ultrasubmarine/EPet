//
//  PlayerSave.cpp
//  EPet
//
//  Created by marina porkhunova on 27.09.2025.
//
#include  <memory>

#include "PlayerSave.hpp"
#include "Game.hpp"
#include "ResourceManager.hpp"
#include "Logging.hpp"
#include "GetPath.hpp"

#include <filesystem>
#include <fstream>


PlayerSave::PlayerSave(IPlayerInfo* playerInfo): _saveInfo(playerInfo)
{
    if(!_saveInfo)
    {
        LOG_ERROR("PlayerSave::PlayerSave(): save info container doesn't set");
    }
}

PlayerSave::~PlayerSave()
{
    if(_saveInfo)
    {
        delete _saveInfo;
    }
}

bool PlayerSave::Save()
{
    auto manager = Game::Instance().GetResourceManager();
    if(!manager)
    {
        LOG_ERROR("PlayerSave::Save(): ResourceManager didn't find.");
        return false;
    }
    if(!_saveInfo)
    {
        LOG_ERROR("PlayerSave::Save(): saveInfo didn't find.");
        return false;
    }
    
    if(!_saveData)
    {
        _saveData = std::unique_ptr<json>(new json()); // accept saving empty json
    }

    // serialize information
    _saveInfo->Save(*_saveData.get());
    
    return manager->SaveJson(_fileName, _saveData.get(), ResourceType::save);
};

bool PlayerSave::Load()
{
    auto manager = Game::Instance().GetResourceManager();
    if(!manager)
    {
        LOG_ERROR("PlayerSave::Load(): ResourceManager didn't find.");
        return false;
    }
    if(!_saveInfo)
    {
        LOG_ERROR("PlayerSave::Load(): save info container doesn't set");
        return false;
    }
    
    if(auto data = manager->GetJson(_fileName, ResourceType::save))
    {
        _saveData = std::unique_ptr<json>(data);
    }
    else  // create new save from start default settings
    {
        LOG_MESSAGE("PlayerSave::Load(): Save file didn't find. Start new game");
        _saveData = std::unique_ptr<json>(new json()); // accept saving empty json
    }

    // deserialize information
    _saveInfo->Load(*_saveData.get());
    return true;
};
