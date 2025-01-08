//
//  JsonLoader.hpp
//  Labirint
//
//  Created by marina porkhunova on 13.02.2023.
//

#ifndef JsonLoader_hpp
#define JsonLoader_hpp

#include <stdio.h>
#include "json.hpp"

using json = nlohmann::json;

class JsonLoader
{
    static json gameSettings;
public:
    ~JsonLoader();
    
    static const json* GetGameSettings();
    static const json* LoadGameSettings(char *fullPath);
   
    const json* GetJson(char *fullPath); /// free memory in json*
    void ConvertToData();
    
};

#endif /* JsonLoader_hpp */
