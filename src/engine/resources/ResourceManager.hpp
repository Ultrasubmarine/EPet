//
//  ResourceManager.hpp
//  Labirint
//
//  Created by marina porkhunova on 12.02.2023.
//

#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include <stdio.h>
#include <memory>

#include "json.hpp"
#include "RenderSystem.hpp"
#include "JsonReadingResult.hpp"

using json = nlohmann::json;

enum class ResourceType
{
    none,
    texture,
    font,
    scene,
    save,
    settings,
    animation,
};

class JsonLoader;
class AnimationLoader;
class ITextureLoader;
class IFontLoader;

struct Texture;
struct Animation;

struct Font;
struct FontSettings;

class ResourceManager
{
    JsonLoader* _jsonLoader;
    ITextureLoader* _textureLoader;
    AnimationLoader* _animationLoader;
    IFontLoader* _fontLoader;
    
    std::filesystem::path _path; // to resources
public:
    ResourceManager();
    ~ResourceManager();
    
    //Json
    std::unique_ptr<json> GetJson(const std::string& title, ResourceType type, JsonReadingResult* result = nullptr) const;
    std::unique_ptr<json> GetJson(const std::filesystem::path& path, JsonReadingResult* result = nullptr) const;
    bool SaveJson(const std::string& title, const json* src, ResourceType type) const;
    
    //Texture
    std::shared_ptr<Texture> GetTexture(const std::string& title);
    
    //TextTexture
    std::shared_ptr<Texture> GetTextTexture(std::string& title, std::shared_ptr<Font> font, const FontSettings &settings);
    
    //Font
    std::shared_ptr<Font> GetFont(std::string& title);
    
    //Animation
    std::shared_ptr<const Animation> GetAnimation(const std::string& title);
    
    //Helper functions
    bool HasFile(const std::filesystem::path& path) const;
    std::filesystem::path BuildResourcePath(const std::string& name, const std::string* format /* could be nullptr */, ResourceType type) const;
    
};
#endif /* ResourceManager_hpp */
