//
//  FontLoader.cpp
//  Labirint -> migrate to Epet with changes
//
//  Created by marina porkhunova on 11.05.2026.
//

#include <iostream>
#include "SDLFontLoader.hpp"

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

#include "SDLRender.hpp"
#include "SDLFont.h"
#include "SDLTextTexture.hpp" // TODO: Delete this

#include "Game.hpp"
#include "Logging.hpp"

#include "Texture.hpp"
#include "SDLTexture.hpp"

#include <variant>

SDL_Color ToSDLColor(const RGBA& c) {
    return SDL_Color{ c.r, c.g, c.b, c.a };
}

SDLFontLoader::SDLFontLoader()
{
    _render = dynamic_cast<SDLRender*>(Game::Instance().GetRender());
    
    if (TTF_Init()==-1) {
        LOG_ERROR("SDLFontLoader::SDLFontLoader() " << SDL_GetError());
        return ;
    }
}

Font* SDLFontLoader::_LoadFont(const std::string& name, const char *fullPath)
{
    auto f = TTF_OpenFont(fullPath, 24);
    if(!f) {
        LOG_ERROR("SDLFontLoader::_LoadFont() error with open ttf font ");
        return nullptr;
    }
    
    auto sdl = std::make_unique<SDLFont>(f);
    auto font = new Font(name, std::move(sdl));

    return font;
}

std::shared_ptr<Texture> SDLFontLoader::GetTexture(std::string& text, std::shared_ptr<Font> font, const FontSettings& settings)
{
    TTF_Font* ttf = nullptr;
    if (auto sdlUPtr = std::get_if<std::unique_ptr<SDLFont>>(&font->resource)) {
        SDLFont* sdlFont = sdlUPtr->get(); // sdlUPtr имеет тип std::unique_ptr<SDLFont>*
        ttf = sdlFont->GetFont();
    }
    else {
        LOG_ERROR("Font resource is not SDLFont");
        return nullptr;
    }

    if (!ttf) {
        LOG_ERROR("GetTextTexture: null TTF_Font");
        return nullptr;
    }

    if (TTF_SetFontSize(ttf, settings.size) == -1) {
        LOG_ERROR("GetTextTexture: TTF_SetFontSize failed: " << TTF_GetError());
        return nullptr;
    }

    // render
    SDL_Color sdlColor = ToSDLColor(settings.color);
    SDL_Surface* surfaceText = TTF_RenderText_Solid(ttf, text.c_str(), sdlColor);
    if (!surfaceText) {
        LOG_ERROR("GetTextTexture: TTF_RenderText_Solid failed: " << TTF_GetError());
        return nullptr;
    }

    SDL_Texture* textTex = SDL_CreateTextureFromSurface(_render->GetRender(), surfaceText);

    SDL_Rect rect{0, 0, surfaceText->w, surfaceText->h};
    SDL_FreeSurface(surfaceText);

    if (!textTex) {
        LOG_ERROR("GetTextTexture: SDL_CreateTextureFromSurface failed: " << SDL_GetError());
        return nullptr;
    }

    SDLTexture* res = new SDLTexture{ textTex, rect};
    auto texturePtr = std::make_shared<Texture>(text, res);
    return texturePtr;
}

