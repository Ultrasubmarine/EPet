//
//  JsonLoader.cpp
//  Labirint
//
//  Created by marina porkhunova on 13.02.2023.
//

#include "JsonLoader.hpp"
#include <fstream>
#include <filesystem>
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
    if (!src) {
        LOG_ERROR("Json is null. File [" << fullPath << "] not saved");
        return false;
    }
    
    const std::filesystem::path path(fullPath);
    auto tmpPath = path;
    tmpPath += ".tmp";
    
    // old tmp, e.g. after crash
    std::error_code error;
    std::filesystem::remove(tmpPath, error);
    
    std::ofstream file(tmpPath, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        LOG_ERROR("Failed to open file [" << tmpPath.string() << "] for writing: " << std::system_category().message(errno));
        return false;
    }
    
    // invalid UTF-8 -> replacement character, without exception
    file<<src->dump(4, ' ', false, json::error_handler_t::replace);
    file.close();
    if (file.fail()) {
        LOG_ERROR("Failed to write file [" << tmpPath.string() << "]");
        std::filesystem::remove(tmpPath, error);
        return false;
    }
    
    std::filesystem::rename(tmpPath, path, error);
    if (error) {
        LOG_ERROR("Failed to rename file [" << tmpPath.string() << "] to [" << path.string() << "]: " << error.message());
        return false;
    }
    return true;
}
