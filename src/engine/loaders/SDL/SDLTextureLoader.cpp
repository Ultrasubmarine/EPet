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

#include "SDLTexture.hpp"

SDLTextureLoader::SDLTextureLoader()
{
    _render = dynamic_cast<SDLRender*>(Game::Instance().GetRender());
}

Texture* SDLTextureLoader::_LoadTexture(const std::string& name, char *fullPath)
{
    if(!_render)
    {
        std::cout<<"error: SDLTextureLoader::LoadTexture() render is empty"<<std::endl;
        return nullptr;
    }
    
    SDL_Surface *bmpSurf = SDL_LoadBMP(fullPath);
    
    SDL_Texture *bmpTex = SDL_CreateTextureFromSurface(_render->GetRender(), bmpSurf);
    
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
    
    std::cout<<"error: SDLTextureLoader::LoadTexture() texture:"<<name;
    return NULL;
}


