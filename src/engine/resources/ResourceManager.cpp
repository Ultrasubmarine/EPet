//
//  ResourceManager.cpp
//  Labirint
//
//  Created by marina porkhunova on 12.02.2023.
//

#include <fstream>
#include "ResourceManager.hpp"
#include "GetPath.hpp"
#include "Logging.hpp"

#include "JsonLoader.hpp"
#include "EngineSettings.h"

ResourceManager::ResourceManager()
{
    _jsonLoader = new JsonLoader();
    _textureLoader = new TextureLoader();
}

ResourceManager::~ResourceManager()
{
    delete _jsonLoader;
    delete _textureLoader;
}

std::shared_ptr<Texture> ResourceManager::GetTexture(std::string& title)
{
    auto t = _textureLoader->GetTexture(title);
    if(t) {
        return t;
    }
    
    std::string r_path ="resources/images/" + title;
    std::string type = "bmp";
    
    char *image_path = GetPath(r_path, &type);
    t = _textureLoader->LoadTexture(title, image_path);
    delete image_path;
    
    return t;
}

//std::shared_ptr<Font> ResourceManager::GetFont(std::string& name)
//{
//    auto ft = _fontLoader->GetFont(name);
//    if(ft)
//        return ft;
//
//    std::string r_path ="resources/fonts/" + name;
//    std::string type = "ttf";
//
//    char *font_path = GetPath(r_path, type);
//    ft = _fontLoader->LoadFont(name, font_path);
//    delete font_path;
//
//    return ft;
//}

//std::shared_ptr<TextTexture> ResourceManager::GetTextTexture(std::string& text, std::string& fontName, int fsize, SDL_Color color)
//{
//    auto font = GetFont(fontName);
//    if(!font)
//        return nullptr;
//
//    return _fontLoader->GetText(text, font, fsize, color);
//}
//
//const json* ResourceManager::GetGameSettings()
//{
//    auto j = JsonLoader::GetGameSettings();
//    if(j)
//        return j;
//    
//    std::string r_path ="resources/game_settings";
//    std::string type = "json";
//    
//    char *json_path = GetPath(r_path, type);
//    j = JsonLoader::LoadGameSettings(json_path);
//    delete json_path;
//    
//    return j;
//}

std::shared_ptr<json> ResourceManager::GetJson(const std::string& title, ResourceType type) const
{
    std::string format = ".json";
    const char *json_path = GetResourcePath(title, &format, type);

    if( !json_path || *json_path == '\0')
    {
        LOG_ERROR("ResourceManager::GetJson() json file (" << title <<") didn't found");
        return nullptr;
    }
    
    auto j = _jsonLoader->GetJson(json_path);
    delete json_path;
    
    return std::shared_ptr<json>{j};
}

bool ResourceManager::SaveJson(const std::string& title,const json* src, ResourceType type) const
{
    std::string empt = "";
    std::string format = ".json";
    const char* _path = GetResourcePath(empt, nullptr, ResourceType::scene); // check only directory path
    
    if(!_path || *_path == '\0')
    {
        LOG_ERROR("ResourceManager::SaveScene() Empty path file(" << title <<"). Saving was canceled.");
        return false;
    }
    
    std::string _full_path = _path + std::string("/") + title + format;
    delete _path;
    
    std::ofstream file(_full_path, std::ios::out | std::ios::trunc | std::ios::app);
    if (!file.is_open()) {
        LOG_ERROR("ResourceManager::SaveScene() Coudn't open sceneFile (" << title <<"). Saving scene was canceled.");
        return false;
    }
    
    file<<src->dump(4);
    file.close();
    
    LOG_MESSAGE("ResourceManager::SaveScene() file (" << title <<") was saved.");
    return true;
}

const char* ResourceManager::GetResourcePath(const std::string& name, const std::string* format, ResourceType type) const
{
    std::string _path ="resources";
    
    switch (type) {
        case ResourceType::texture:
        {
            _path += "/images";
            break;
        }
        case ResourceType::font:
        {
            _path += "/fonts";
            break;
        }
        case ResourceType::scene:
        {
            _path += "/scenes";
            break;
        }
        case ResourceType::save:
        {
            _path += "/saves";
            break;
        }
        default:
            break;
    }
    _path += name.empty()? "" : "/" + name;
    
    return GetPath(_path, format);
}
