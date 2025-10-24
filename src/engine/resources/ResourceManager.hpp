//
//  ResourceManager.hpp
//  Labirint
//
//  Created by marina porkhunova on 12.02.2023.
//

#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include <stdio.h>
#include "json.hpp"

#include "RenderSystem.hpp"

using json = nlohmann::json;

enum class ResourceType
{
    none,
    texture,
    font,
    scene,
    save,
    settings
};

class JsonLoader;
class ITextureLoader;

struct Texture;

class ResourceManager
{
    JsonLoader* _jsonLoader;
    ITextureLoader* _textureLoader;
    
    std::filesystem::path _path; // to resources
public:
    ResourceManager();
    ~ResourceManager();
    
    //Json
    std::shared_ptr<json> GetJson(const std::string& title, ResourceType type) const;
    bool SaveJson(const std::string& title, const json* src, ResourceType type) const;
    
    //Texture
    std::shared_ptr<Texture> GetTexture(std::string& title);
    
    //Helper functions
    std::filesystem::path GetResourcePath(const std::string& name, const std::string* format /* could be nullptr */, ResourceType type) const;
    
};
#endif /* ResourceManager_hpp */
