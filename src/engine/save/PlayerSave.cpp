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
    std::filesystem::path cwd = GetResourcePath();
    
    auto file = manager->GetJson(_fileName, ResourceType::save);
    if(!file)
    {
        LOG_MESSAGE("PlayerSave::Load() player save didn't find.");
        return false;
    }
    
    // TODO: maybe bad solution
    if(file.use_count() == 1)
    {
       json* raw_tmp = file.get();
       file.reset();
       _save = std::unique_ptr<json>(raw_tmp);
    }
    else
    {
       LOG_ERROR("PlayerSave::Load() : player save downloaded but loader keep smart pointer.");
       
       json* another = new json( *file.get());
       _save = std::unique_ptr<json>(another);
    }
    
    return true;
};

