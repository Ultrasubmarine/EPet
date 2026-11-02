//
//  PlayerSave.hpp
//  EPet
//
//  Created by marina porkhunova on 27.09.2025.
//

#ifndef PlayerSave_hpp
#define PlayerSave_hpp

#include <stdio.h>
#include <memory>
#include <string>

#include "json.hpp"
#include "Logger.hpp"
#include "JsonUtils.hpp"

using json = nlohmann::json;

class PlayerSave
{
    const std::string _fileName = "save";
    std::unique_ptr<json> _saveData = nullptr;
    
public:
    
    bool Save();
    bool Load();
    
    json* GetData() { return _saveData.get();}
};


/// lastUpdate - unix time, in seconds
inline bool GetAttribute(json* from, const char* attribute_name, int& value, std::time_t& lastUpdate)
{
    if(!from)
    {
        LOG_ERROR("Save data is null. Attribute [" << attribute_name << "] not loaded");
        return false;
    }

    const std::string attr = std::string("/") + attribute_name;
    if(!from->contains(json::json_pointer(attr)))
    {
        return false;
    }
    
    auto success = false;
    success = ReadValue<int>(*from, attr + "/value", value);
    success &= ReadValue<std::time_t>(*from, attr + "/lastUpdate", lastUpdate);
    
    return success;
}

/// lastUpdate - unix time, in seconds
inline void SetAttribute(json* to, const char* attribute_name, const int value, const std::time_t lastUpdate)
{
    if(!to)
    {
        LOG_ERROR("Save data is null. Attribute [" << attribute_name << "] not saved");
        //TODO do smth for player + share logs
        return;
    }
    
    const std::string attr = std::string("/") + attribute_name;
    
    WriteValue<int>(*to, attr + "/value", value);
    WriteValue<std::time_t>(*to, attr + "/lastUpdate", lastUpdate);
}

// TODO: Add function for easy get common atributes

#endif /* PlayerSave_hpp */
