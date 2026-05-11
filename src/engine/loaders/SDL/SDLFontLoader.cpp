//
//  FontLoader.cpp
//  Labirint -> migrate to Epet with changes
//
//  Created by marina porkhunova on 11.05.2026.
//

#include <iostream>
#include "SDLFontLoader.hpp"

#include "SDLRender.hpp"
#include "Game.hpp"
#include "Font.hpp"

#include "Logging.hpp"


SDLFontLoader::SDLFontLoader()
{
    _render = dynamic_cast<SDLRender*>(Game::Instance().GetRender());
    
    if (TTF_Init()==-1) {
        LOG_ERROR("SDLFontLoader::SDLFontLoader() " << SDL_GetError());
        return ;
    }
}


//std::shared_ptr<Font> SDLFontLoader::LoadFont(std::string& name, char *fullPath)
//{
//    auto f =TTF_OpenFont(fullPath, 24);
//    std::shared_ptr<Font> font{new Font{name,f}, [this](Font *f){ this->DeleteFont(f);} };
//    
//    if(font)
//    {
//        _fonts[name] = std::weak_ptr<Font>{font};
//        return font;
//    }
//    
//    return nullptr;
//}


Font* SDLFontLoader::_LoadFont(const std::string& name, const char *fullPath)
{
    auto f = TTF_OpenFont(fullPath, 24);
    if(f) {
        LOG_ERROR("SDLFontLoader::_LoadFont() error with open ttf font ");
        return nullptr;
    }
    
    std::shared_ptr<Font> font{new Font{name,f}, [this](Font *f){ this->DeleteFont(f);} };
    if(font) {
        _fonts[name] = std::weak_ptr<Font>{font};
        return font;
    }
    return nullptr;
}


