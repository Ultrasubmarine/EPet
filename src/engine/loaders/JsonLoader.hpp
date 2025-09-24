//
//  JsonLoader.hpp
//  Labirint
//
//  Created by marina porkhunova on 13.02.2023.
//

#ifndef JsonLoader_hpp
#define JsonLoader_hpp

#include <stdio.h>
#include <memory>
#include "json.hpp"

using json = nlohmann::json;

class JsonLoader
{
    static json gameSettings; // ???
    
public:
    ~JsonLoader();
    
    static const json* GetGameSettings();
    static const json* LoadGameSettings(char *fullPath);
   
    std::shared_ptr<const json> GetJson(char *fullPath);
    void SaveJson(char *fullPath, const json* src);
    
    void ConvertToData();
    
};

#endif /* JsonLoader_hpp */
