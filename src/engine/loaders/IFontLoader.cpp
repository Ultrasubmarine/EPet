//
//  FontLoader.cpp
//  Labirint
//
//  Created by marina porkhunova on 25.02.2023.
//

#include <iostream>

#include "IFontLoader.hpp"
#include "Font.hpp"
#include "Logging.hpp"

void IFontLoader::DeleteFont(Font* font)
{
    _fonts.erase(font->name);
    delete font;
}

std::shared_ptr<Font> IFontLoader::GetFont(const std::string& name)
{
    if(auto it = _fonts.find(name); it != _fonts.end())
        return it->second.lock();
    
    return nullptr;
}

std::shared_ptr<Font> IFontLoader::LoadFont(const std::string& name, char *fullPath)
{
    if(auto resource = _LoadFont(name, fullPath))
    {
        std::shared_ptr<Font> font{ resource, [this](Font* t){ this->DeleteFont(t);}};
        
        _fonts[name] = std::weak_ptr<Font>{font};
        return font;
    }
    
    LOG_ERROR("IFontLoader::LoadFont() font:"<<name);
    return NULL;
}


//std::shared_ptr<TextTexture> FontLoader::GetText(std::string& text, std::shared_ptr<Font> font, int fsize, SDL_Color color)
//{
//    if( TTF_SetFontSize( font.get()->font, fsize) == -1)
//    {
//        std::cout<<"error: FontLoader::GetText() set size. \ntext:"""<<text<<""" \nsize:"<<fsize<<"\n";
//    }
//    
//    SDL_Surface* surfaceText = TTF_RenderText_Solid(font.get()->font, text.c_str(), color);
//    SDL_Texture* textTex = SDL_CreateTextureFromSurface(_render, surfaceText);
//    
//    SDL_Rect rect;
//    rect.x = 0;
//    rect.y = 0;
//    rect.w = surfaceText->w;
//    rect.h = surfaceText->h;
//    SDL_FreeSurface(surfaceText);
//
//    if(textTex)
//        return std::shared_ptr<TextTexture>( new TextTexture{ textTex, font, text, color, rect});
//    
//    std::cout<<"error: FontLoader::GetText() text:"<<text;
//    return NULL;
//}


