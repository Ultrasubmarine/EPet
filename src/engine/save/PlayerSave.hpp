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
#include "Logging.hpp"

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


inline bool GetAttribute(json* from, const char* attribute_name, int& value, std::time_t& lastUpdate)
{
    if(!from)
    {
        //error
        return false;
    }
    
    if((*from).contains(attribute_name) && (*from)[attribute_name].is_object()) {
        const auto& levelObj = (*from)[attribute_name];
        if(levelObj.contains("value") && levelObj["value"].is_number_integer()) {
            value = levelObj["value"].get<int>();
        }
        if(levelObj.contains("lastUpdate") && levelObj["lastUpdate"].is_number_integer()) {
            lastUpdate = levelObj["lastUpdate"];
        }
    }
    
    return true;
}

inline void SetAttribute(json* from, const char* attribute_name, int& value, std::time_t& lastUpdate)
{
    if(!from)
    {
        LOG_ERROR("GrowingSystem::LoadAge() saveData doesn't exist. Loading hamster level skipped");
        //TODO do smth for player + share logs
        return;
    }
    
}

// TODO: Add function for easy get common atributes

#endif /* PlayerSave_hpp */
