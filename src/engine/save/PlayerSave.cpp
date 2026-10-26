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
#include "Logger.hpp"

bool PlayerSave::Save()
{
    auto manager = Game::Instance().GetResourceManager();
    if(!manager)
    {
        LOG_ERROR("Resource manager is null. Saving canceled");
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
        LOG_ERROR("Resource manager is null. Loading canceled");
        return false;
    }
    
    if(auto data = manager->GetJson(_fileName, ResourceType::save))
    {
        _saveData = std::move(data);
        saveFinded = true;
    }
    else  // create new empty save 
    {
        LOG_MESSAGE("Save file not found. Start new game");
        _saveData = std::unique_ptr<json>(new json({})); // accept saving empty json
    }

    return saveFinded;
};




