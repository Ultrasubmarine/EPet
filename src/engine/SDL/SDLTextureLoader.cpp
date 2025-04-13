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

struct SDLTexture {
   SDL_Texture *texture;
   SDL_Rect src;
    
    ~SDLTexture()
    {
        SDL_DestroyTexture(texture);
    }
};

SDLTextureLoader::SDLTextureLoader()
{
    _render = dynamic_cast<SDLRender*>(Game::Instance().GetRender());
}

Texture* SDLTextureLoader::_LoadTexture(std::string& name, char *fullPath)
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
        //TODO: make sure that this f*king function doesn't start to leak memory
        //TODO: is it okey that my resource is combined by two different resources in memmory? 
        std::function<void(void*)> deleter = [](void* resource)
        {
            auto res = static_cast<SDLTexture*>(resource);
            delete res;
        };
        
        SDLTexture* res = new SDLTexture{ bmpTex, src};
        return new Texture{name, res, deleter};
    }
    
    std::cout<<"error: SDLTextureLoader::LoadTexture() texture:"<<name;
    return NULL;
}


