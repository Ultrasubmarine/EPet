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
        //TODO: make sure that this f*king function doesn't start to leak memory
        //TODO: is it okey that my resource is combined by two different resources in memmory? 
        std::function<void(void*)> deleter = [](void* resource)
        {
            auto res = static_cast<SDLTexture*>(resource);
            delete res;
        };
        
        SDLTexture* res = new SDLTexture{ bmpTex, src};
        
        auto t = Texture{name, res, deleter};
        // TMP TEST
        SDL_Rect f(10,10, 150,150);
        auto ren = dynamic_cast<SDLRender*>(Game::Instance().GetRender());
        
        SDL_SetRenderDrawColor(ren->GetRender(), 0xFF, 0xA, 0xA, 0xFF);
       // SDL_RenderClear(ren->GetRender());
        
        SDLTexture* txt = static_cast<SDLTexture*>(t.resource);
        SDL_RenderCopy(ren->GetRender(), txt->texture, &f, &f);
        
       // SDL_RenderCopy(ren->GetRender(), bmpTex, &src, &f);
        ren->Present();
        /// END TMP TEST
    
        return new Texture{name, res, deleter};
    }
    
    std::cout<<"error: SDLTextureLoader::LoadTexture() texture:"<<name;
    return NULL;
}


