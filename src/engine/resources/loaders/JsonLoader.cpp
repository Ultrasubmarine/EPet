//
//  JsonLoader.cpp
//  Labirint
//
//  Created by marina porkhunova on 13.02.2023.
//

#include "JsonLoader.hpp"
#include <fstream>
#include "Logger.hpp"

JsonLoader::~JsonLoader()
{
}

void JsonLoader::ConvertToData()
{
}

json* JsonLoader::GetJson(const char *fullPath)
{
    std::ifstream buff(fullPath);
    
    json* j = nullptr;
    if(buff.is_open())
    {
        json parsed = json(json::parse(buff, nullptr, false));
        buff.close();
        
        if(parsed.is_discarded())
        {
            LOG_ERROR("json parse failed. file: "<< fullPath);
            return nullptr;
        }
        
        j = new json(std::move(parsed));
    }
    else
    {
        LOG_ERROR("couldn't open file. file: "<< fullPath <<". error: " <<std::system_category().message(errno));
    }
    return j;
}

bool JsonLoader::SaveJson(const char *fullPath, const json* src)
{
    std::ofstream file(fullPath, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        LOG_ERROR("couldn't open file. error: " <<std::system_category().message(errno)<<". path:"<<fullPath);
        return false;
    }
    
    file<<src->dump(4);
    file.close();
    return true;
}
