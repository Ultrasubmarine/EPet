//
//  ResourceManager.hpp
//  Labirint
//
//  Created by marina porkhunova on 12.02.2023.
//

#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include <fstream>
#include <stdio.h>
#include <map>

#include "json.hpp"

#include "RenderSystem.hpp"

using json = nlohmann::json;

enum class ResourceType
{
    texture,
    font,
    scene
};

class JsonLoader;

class ResourceManager
{
    JsonLoader* _jsonLoader;
    
public:
    ResourceManager();
    ~ResourceManager();
    
  //  static const json* GetGameSettings();
    const json* GetSceneSettings(std::string title);
    
    const char* GetResourcePath(ResourceType type, std::string& name, std::string format);
};
#endif /* ResourceManager_hpp */
