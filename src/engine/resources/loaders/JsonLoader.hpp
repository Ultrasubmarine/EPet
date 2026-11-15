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
#include "JsonReadingResult.hpp"

using json = nlohmann::json;

class JsonLoader
{
public:
    
    std::unique_ptr<json> GetJson(const char *fullPath, JsonReadingResult* result = nullptr);
    bool SaveJson(const char *fullPath, const json* src);
};

#endif /* JsonLoader_hpp */
