//
//  ResourceManager.cpp
//  Labirint
//
//  Created by marina porkhunova on 12.02.2023.
//

#include <fstream>
#include "ResourceManager.hpp"
#include "GetPath.hpp"
#include "Logger.hpp"

#include "JsonLoader.hpp"
#include "AnimationLoader.hpp"
#include "IFontLoader.hpp"

#include "EngineSettings.h"

ResourceManager::ResourceManager()
{
    _path = ::GetResourcePath();
    
    _jsonLoader = new JsonLoader();
    _textureLoader = new TextureLoader();
    _animationLoader = new AnimationLoader(this);
    _fontLoader = new FontLoader();
}

ResourceManager::~ResourceManager()
{
    delete _animationLoader;
    delete _jsonLoader;
    delete _textureLoader;
}

std::shared_ptr<Texture> ResourceManager::GetTexture(std::string& title)
{
    if (auto t = _textureLoader->GetTexture(title)) {
        return t;
    }
    
    std::string format = ".bmp";
    
    auto path = BuildResourcePath(title, &format, ResourceType::texture);
    if (HasFile(path)) {
        auto t = _textureLoader->LoadTexture(title, path.c_str());
        return t;
    }
  
    LOG_ERROR("Image [" << title << "] not found");
    return nullptr;
}

//TextTexture
std::shared_ptr<Texture> ResourceManager::GetTextTexture(std::string& title, std::shared_ptr<Font> font, const FontSettings &settings)
{
    if(!_fontLoader) {
        return nullptr;
    }
    
    return _fontLoader->GetTexture(title, font, settings);
}

std::shared_ptr<Font> ResourceManager::GetFont(std::string& title)
{
    if(!_fontLoader) {
        return nullptr;
    }
    
    if(auto f = _fontLoader->GetFont(title))
    {
        return f;
    }
        
    std::string format = ".ttf";
    
    auto path = BuildResourcePath(title, &format, ResourceType::font);
    if (HasFile(path)) {
        auto f = _fontLoader->LoadFont(title, path.c_str());
        return f;
    }
    
    LOG_ERROR("Font [" << title << "] not found");
    return nullptr;
}

std::unique_ptr<json> ResourceManager::GetJson(const std::string& title, ResourceType type, JsonReadingResult* result) const
{
    std::string format = ".json";
    
    auto json_path = BuildResourcePath(title, &format, type);
    if(HasFile(json_path))
    {
        auto j = _jsonLoader->GetJson(json_path.string().c_str(), result);
        return j;
    }
    
    if (result) {
        *result = JsonReadingResult::NotFound; // caller handles it
    }
    else {
        LOG_ERROR("JSON [" << title << "] not found");
    }
    return nullptr;
}

std::unique_ptr<json> ResourceManager::GetJson(const std::filesystem::path& path, JsonReadingResult* result) const
{
    if(HasFile(path))
    {
        auto j = _jsonLoader->GetJson(path.string().c_str(), result);
        return j;
    }
    
    LOG_ERROR("JSON from path [" << path << "] not found");
    if (result) *result = JsonReadingResult::NotFound;
    return nullptr;
}

bool ResourceManager::SaveJson(const std::string& title,const json* src, ResourceType type) const
{
    std::string empt = "";
    std::string format = ".json";
    
    //TODO: really bad solution to use 2 ifs where first - negative/error behaviour, second - positive. it's mess.
    auto path = BuildResourcePath(empt, nullptr, type); // check only directory path
    if(!HasFile(path))
    {
        LOG_ERROR("Directory for [" << title << "] not found. Saving canceled");
        return false;
    }
    
    std::string fullPath = path / (title + format);
    if(_jsonLoader->SaveJson(fullPath.c_str(), src))
    {
        LOG_MESSAGE("File [" << title << "] saved");
        return true;
    }
    return false;
}

//Animation
std::shared_ptr<const Animation> ResourceManager::GetAnimation(const std::string& title)
{
    if (title.empty())
    {
        LOG_ERROR("Animation name is empty");
    }
    
    if (auto a = _animationLoader->GetAnimation(title)) {
        return a;
    }
    
    std::string format = ".json";
    auto path = BuildResourcePath(title, &format, ResourceType::animation);
    if (HasFile(path)) {
        auto a = _animationLoader->LoadAnimation(title, path.c_str());
        return a;
    }
  
    LOG_ERROR("Animation [" << title << "] not found");
    return nullptr;
}

bool ResourceManager::HasFile(const std::filesystem::path& file) const
{
    return fs::exists(file);
}

std::filesystem::path ResourceManager::BuildResourcePath(const std::string& name, const std::string* format, ResourceType type) const
{
    auto candidate = _path;
    
    switch (type) {
        case ResourceType::texture:
        {
            candidate += "/images";
            break;
        }
        case ResourceType::font:
        {
            candidate += "/fonts";
            break;
        }
        case ResourceType::scene:
        {
            candidate += "/scenes";
            break;
        }
        case ResourceType::animation:
        {
            candidate += "/animations";
            break;
        }
        case ResourceType::save:
        {
            candidate = GetSavePath();
            break;
        }
        default:
            break;
    }
    
    candidate += name.empty()? "" : ("/" + name + *format);
    return candidate;
}
