//
//  JsonLoader.cpp
//  Labirint
//
//  Created by marina porkhunova on 13.02.2023.
//

#include "JsonLoader.hpp"
#include <fstream>

json JsonLoader::gameSettings{};

JsonLoader::~JsonLoader()
{
}

void JsonLoader::ConvertToData()
{
    
}

const json* JsonLoader::LoadGameSettings(char *fullPath)
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

const json* JsonLoader::GetJson(char *fullPath)
{
    std::ifstream buff(fullPath);
    auto* j = new json(json::parse(buff));
    buff.close();
    return j;
}
