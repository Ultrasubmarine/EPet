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
    _path = ::GetResourcePath();
    
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
    
    std::string format = ".bmp";
    if (auto path = GetResourcePath(title, &format, ResourceType::texture); !path.empty()) {
        t = _textureLoader->LoadTexture(title, path.c_str());
    }
    else
    {
        LOG_ERROR("image " << title <<"didn't find");
    }
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
    
    auto json_path = GetResourcePath(title, &format, type);

    if(json_path.empty())
    {
        LOG_ERROR("ResourceManager::GetJson() json file (" << title <<") didn't found");
        return nullptr;
    }
    
    auto j = _jsonLoader->GetJson(json_path.string().c_str());
    return std::shared_ptr<json>{j};
}

bool ResourceManager::SaveJson(const std::string& title,const json* src, ResourceType type) const
{
    std::string empt = "";
    std::string format = ".json";
    auto path = GetResourcePath(empt, nullptr, ResourceType::scene); // check only directory path
    
    if(path.empty())
    {
        LOG_ERROR("ResourceManager::SaveScene() Empty path file(" << title <<"). Saving was canceled.");
        return false;
    }
    
   // std::string _full_path = path / title + format;
  //  delete path;
    
//    std::ofstream file(_full_path, std::ios::out | std::ios::trunc | std::ios::app);
//    if (!file.is_open()) {
//        LOG_ERROR("ResourceManager::SaveScene() Coudn't open sceneFile (" << title <<"). Saving scene was canceled.");
//        return false;
//    }
//    
//    file<<src->dump(4);
//    file.close();
//    
//    LOG_MESSAGE("ResourceManager::SaveScene() file (" << title <<") was saved.");
    return true;
}

std::filesystem::path ResourceManager::GetResourcePath(const std::string& name, const std::string* format, ResourceType type) const
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
        case ResourceType::save:
        {
            candidate += "/saves"; // TODO: FULL CHANGE 
            break;
        }
        default:
            break;
    }
    
    candidate += name.empty()? "" : ("/" + name + *format);
    if (fs::exists(candidate)) {
        return candidate;
    }
   
    LOG_ERROR("ResourceManager::GetResourcePath() file (name:" << name <<" format:"<< format << ") didn't found. searching directory:"<< candidate);
    return std::filesystem::path();
}
