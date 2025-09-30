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
    if(auto manager = Game::Instance().GetResourceManager())
    {
        return manager->SaveJson(_fileName, _save.get());
    }
    return false;
};

bool PlayerSave::Load()
{
    if(auto manager = Game::Instance().GetResourceManager())
    {
        if(auto file = manager->GetJson(_fileName))
        {
            _save = std::unique_ptr<json>(std::move(file)); // TODO: check/add json* deleter
            
            std::string type = "json";
            manager->GetResourcePath(ResourceType::save, _fileName, type);
            
            if(_save->empty())
                return false;
            return true;
        }
        else
        {
            
            // TODO: create default/new
            LOG_MESSAGE("PlayerSave::Load(): player save file didn't find.");
            return false;
        }
    }
    return false;
   
};

