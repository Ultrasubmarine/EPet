//
//  ResourceManager.cpp
//  Labirint
//
//  Created by marina porkhunova on 12.02.2023.
//

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
    
    char *image_path = GetPath(r_path, type);
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

const json* ResourceManager::LoadScene(std::string title)
{
    std::string r_path ="resources/scenes/" + title;
    std::string type = "json";
    
    char *json_path = GetPath(r_path, type);
    
    if(*json_path == '\0')
    {
        LOG_ERROR("ResourceManager::GetScene() scene (" << title <<") didn't found");
        return nullptr;
    }
    
    auto j =   _jsonLoader->GetJson(json_path);
    delete json_path;
    
    return j;
}

void ResourceManager::SaveScene(const std::string& title, json* scene) const
{
    // TODO: temporary crutch for macOS. xcode build application and doesn't see working directory. only app directory. it's hard set path to save
    static char *rootPath = "/Users/sbm/Projects/EPet/resources/";
    
    std::ofstream sceneFile;
    sceneFile.open(title + ".json");
    if(sceneFile.is_open())
    {
        sceneFile<<scene;
    }
    else{
        LOG_ERROR("ResourceManager::SaveScene() Coudn't open sceneFile (" << title <<"). Saving scene was canceled.");
    }
    sceneFile.close();
}

const char* ResourceManager::GetResourcePath(ResourceType type, std::string& name, std::string format)
{
    std::string _path ="resources/";
    
    switch (type) {
        case ResourceType::texture:
        {
            _path += "images/";
            break;
        }
        case ResourceType::font:
        {
            _path += "fonts/";
            break;
        }
        case ResourceType::scene:
        {
            _path += "scenes/";
            break;
        }
        default:
            return nullptr;
    }
    _path += name;
    
    char *full_path = GetPath(_path, format);
    return full_path;
}
