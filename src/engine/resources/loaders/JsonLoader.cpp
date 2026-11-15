//
//  JsonLoader.cpp
//  Labirint
//
//  Created by marina porkhunova on 13.02.2023.
//

#include "JsonLoader.hpp"
#include <fstream>
#include "Logger.hpp"

std::unique_ptr<json> JsonLoader::GetJson(const char *fullPath, JsonReadingResult* result)
{
    std::ifstream buff(fullPath);
    
    if(buff.is_open())
    {
        json parsed = json::parse(buff, nullptr, false);
        buff.close();
        
        if(parsed.is_discarded())
        {
            LOG_ERROR("Failed to parse json [" << fullPath << "]");
            if (result) *result = JsonReadingResult::BrokenFile;
            return nullptr;
        }
        if (result) *result = JsonReadingResult::Success;
        return std::make_unique<json>(std::move(parsed));
    }
    else
    {
        if (result) *result = JsonReadingResult::OpenProblem;
        LOG_ERROR("Failed to open file [" << fullPath << "]: " << std::system_category().message(errno));
    }
    return nullptr;
}

bool JsonLoader::SaveJson(const char *fullPath, const json* src)
{
    std::ofstream file(fullPath, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        LOG_ERROR("Failed to open file [" << fullPath << "] for writing: " << std::system_category().message(errno));
        return false;
    }
    
    file<<src->dump(4);
    file.close();
    return true;
}
