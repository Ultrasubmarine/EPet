//
//  PlayerSave.cpp
//  EPet
//
//  Created by marina porkhunova on 27.09.2025.
//
#include  <memory>
#include <filesystem>

#include "PlayerSave.hpp"

#include "Game.hpp"
#include "Time.hpp"
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
    
    JsonReadingResult result = JsonReadingResult::None;
    auto data = manager->GetJson(_fileName, ResourceType::save, &result);
    
    switch(result) {
        case JsonReadingResult::Success:
        {
            _saveData = std::move(data);
            saveFinded = true;
            break;
        }
        case JsonReadingResult::BrokenFile:
        {
            LOG_ERROR("Save file [" << _fileName << ".json] is broken. Start new game");
            BackupBrokenSave(manager);
            _saveData = std::unique_ptr<json>(new json({}));
            break;
        }
        case JsonReadingResult::NotFound:
        {
            LOG_MESSAGE("Save file not found. Start new game");
            _saveData = std::unique_ptr<json>(new json({})); // accept saving empty json
            break;
        }
        case JsonReadingResult::OpenProblem:
        {
            //TODO: ask player to reload or start new game. 
        }
        default:
        {
            LOG_ERROR("Failed to load save file [" << _fileName << ".json]. Reason [" << ToString(result) << "]. Start new game");
            _saveData = std::unique_ptr<json>(new json({}));
            break;
        }
    }
            
    return saveFinded;
};

bool PlayerSave::BackupBrokenSave(ResourceManager* manager)
{
    const std::string format = ".json";
    const auto path = manager->BuildResourcePath(_fileName, &format, ResourceType::save);
    
    auto backupPath = path;
    const auto date = Time::Instance().GetClockTimeString("%Y-%m-%d_%H-%M-%S");
    backupPath.replace_filename(_fileName + "_broken_" + date + format);
    
    std::error_code error;
    std::filesystem::rename(path, backupPath, error);
    if(error)
    {
        LOG_ERROR("Failed to rename file [" << path.string() << "] to [" << backupPath.string() << "]: " << error.message());
        return false;
    }
    
    LOG_MESSAGE("Broken save moved to [" << backupPath.string() << "]");
    return true;
}




