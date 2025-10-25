//
//  JsonLoader.cpp
//  Labirint
//
//  Created by marina porkhunova on 13.02.2023.
//

#include "JsonLoader.hpp"
#include <fstream>
#include "Logging.hpp"

json JsonLoader::gameSettings{};

JsonLoader::~JsonLoader()
{
}

void JsonLoader::ConvertToData()
{
}

const json* JsonLoader::LoadGameSettings(const char *fullPath)
{
    std::ifstream buff(fullPath);
    gameSettings = json::parse(buff);
    buff.close();
    
    return &gameSettings;
}

const json* JsonLoader::GetGameSettings()
{
    if(gameSettings.empty())
        return nullptr;
    return &gameSettings;
}

json* JsonLoader::GetJson(const char *fullPath)
{
    std::ifstream buff(fullPath);
    
    json* j = nullptr;
    if(buff.is_open())
    {
        j = new json(json::parse(buff));
        buff.close();
    }
    else
    {
        LOG_ERROR(" JsonLoader::GetJson() couldn't open file. error: " <<std::system_category().message(errno));
    }
    return j;
}

bool JsonLoader::SaveJson(const char *fullPath, const json* src)
{
    std::ofstream file(fullPath, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        LOG_ERROR("ResourceManager::SaveJson couldn't open file. error: " <<std::system_category().message(errno)<<"\n path:"<<fullPath);
        return false;
    }
    
    file<<src->dump(4);
    file.close();
    return true;
}
