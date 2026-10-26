//
//  SDLTextureLoader.cpp
//  EPet
//
//  Created by marina porkhunova on 11.04.2025.
//

#include <iostream>
#include <SDL2/SDL.h>

#include "SDLTextureLoader.hpp"
#include "SDLRender.hpp"
#include "Game.hpp"
#include "Logger.hpp"

#include "SDLTexture.hpp"

SDLTextureLoader::SDLTextureLoader()
{
}

Texture* SDLTextureLoader::_LoadTexture(const std::string& name, const char *fullPath)
{
    auto render = dynamic_cast<SDLRender*>(Game::Instance().GetRender());
    if(!render)
    {
        LOG_ERROR("Render is null. Texture not loaded");
        return nullptr;
    }
    
    SDL_Surface *bmpSurf = SDL_LoadBMP(fullPath);
    if(!bmpSurf)
    {
        LOG_ERROR("SDL_LoadBMP failed [" << fullPath << "]: " << SDL_GetError());
        return nullptr;
    }
    
    SDL_Texture *bmpTex = SDL_CreateTextureFromSurface(render->GetRender(), bmpSurf);
    
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = bmpSurf->w;
    src.h = bmpSurf->h;
    SDL_FreeSurface(bmpSurf);
    
    if(bmpTex)
    {
        SDLTexture* res = new SDLTexture{ bmpTex, src};
        return new Texture{name, res};
    }
    
    LOG_ERROR("Failed to create texture [" << name << "]: " << SDL_GetError());
    return NULL;
}


