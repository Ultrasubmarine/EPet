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

using json = nlohmann::json;

struct IPlayerInfo
{
    virtual void Save(json& data) = 0;
    virtual void Load(const json& data) = 0;
    
    virtual void SetDefault() = 0;
};

class PlayerSave
{
    const std::string _fileName = "save";
    std::string _fullPath;
    
    std::unique_ptr<json> _save = nullptr;
    IPlayerInfo* _saveInfo;
    
public:
    bool Save();
    bool Load();
    
    IPlayerInfo* GetSave() { return _saveInfo;};
};

#endif /* PlayerSave_hpp */
