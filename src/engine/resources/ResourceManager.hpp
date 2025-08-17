//
//  ResourceManager.hpp
//  Labirint
//
//  Created by marina porkhunova on 12.02.2023.
//

#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include <stdio.h>
//#include <fstream>

//#include <map>

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
    const json* LoadScene(std::string title);
    void SaveScene(const std::string& title,json* scene) const;
    
    const char* GetResourcePath(ResourceType type, std::string& name, std::string format);
    
    std::shared_ptr<Texture> GetTexture(std::string& title);
};
#endif /* ResourceManager_hpp */
