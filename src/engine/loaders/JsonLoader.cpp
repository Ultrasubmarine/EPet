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
        std::perror("Причина (errno)");
        LOG_ERROR(" JsonLoader::GetJson() couldn't open file. error:" <<std::perror);
    }
    
//    auto deleter = [](const json* j)
//    {
//        LOG_MESSAGE("Json file deleted "<<j->type_name());
//        delete j;
//    };
    return j;
}

void JsonLoader::SaveJson(const char *fullPath, const json* src)
{
    
}
