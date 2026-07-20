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

bool PlayerSave::Save()
{
    auto manager = Game::Instance().GetResourceManager();
    if(!manager)
    {
        LOG_ERROR("PlayerSave::Save(): ResourceManager didn't find.");
        return false;
    }
    
    if(!_saveData)
    {
        _saveData = std::unique_ptr<json>(new json()); // accept saving empty json
    }
    
    return manager->SaveJson(_fileName, _saveData.get(), ResourceType::save);
};

bool PlayerSave::Load()
{
    bool saveFinded = false;
    auto manager = Game::Instance().GetResourceManager();
    if(!manager)
    {
        LOG_ERROR("PlayerSave::Load(): ResourceManager didn't find.");
        return false;
    }
    
    if(auto data = manager->GetJson(_fileName, ResourceType::save))
    {
        _saveData = std::unique_ptr<json>(data);
        saveFinded = true;
    }
    else  // create new empty save 
    {
        LOG_MESSAGE("PlayerSave::Load(): Save file didn't find. Start new game");
        _saveData = std::unique_ptr<json>(new json({})); // accept saving empty json
    }

    return saveFinded;
};




