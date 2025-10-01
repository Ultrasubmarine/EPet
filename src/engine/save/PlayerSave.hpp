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

class PlayerSave
{
    const std::string _fileName = "playerSave";
    
    std::unique_ptr<json> _save = nullptr;
    std::string _fullPath;
    
public:
    bool Save();
    bool Load();
    
//std::weak_ptr<json> GetSave() { return std::weak_ptr<json>{_save};};
};

#endif /* PlayerSave_hpp */
