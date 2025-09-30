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
    texture,
    font,
    scene,
    save
};

class JsonLoader;
class ITextureLoader;

struct Texture;

class ResourceManager
{
    JsonLoader* _jsonLoader;
    ITextureLoader* _textureLoader;
    
public:
    ResourceManager();
    ~ResourceManager();
    
  //  static const json* GetGameSettings();
    std::shared_ptr<const json> LoadScene(std::string title);
    void SaveScene(const std::string& title, json* scene) const;
    
    json* GetJson(const std::string& title /*, ResourceType??? */) const;
    bool SaveJson(const std::string& title, const json* src) const;
  //  std::weak_ptr<json> GetSave(); // file with player progress saving information
    
    const char* GetResourcePath(ResourceType type, const std::string& name, const std::string& format) const;
    
    std::shared_ptr<Texture> GetTexture(std::string& title);
};
#endif /* ResourceManager_hpp */
