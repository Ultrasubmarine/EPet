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
bool PlayerSave::Save()
{
    auto manager = Game::Instance().GetResourceManager();
    if(!manager)
    {
        LOG_ERROR("PlayerSave::Save(): ResourceManager didn't find.");
        return false;
    }
    
    if(!_save)
    {
        _save = std::unique_ptr<json>(new json()); // accept saving empty json
    }
    
    return manager->SaveJson(_fileName, _save.get(), ResourceType::save);
};

bool PlayerSave::Load()
{
    auto manager = Game::Instance().GetResourceManager();
    if(!manager)
    {
        LOG_ERROR("PlayerSave::Load(): ResourceManager didn't find.");
        return false;
    }
    
    auto save_json = manager->GetJson(_fileName, ResourceType::save);
    if(!save_json || save_json.get()->empty())
    {
        LOG_MESSAGE("PlayerSave::Load(): Save file didn't find.");
    }
    else
    {
        // create new save from start default settings
    }
    
    json another;
    another["smth"] = 605;
    
    manager->SaveJson(_fileName, &another, ResourceType::save);
    return true;
};

