//
//  SDLRender.cpp
//  EPet
//
//  Created by marina porkhunova on 03.08.2024.
//

#include "SDLRender.hpp"

#include "SDLTextureLoader.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

#include "SDLWindow.h"
#include "Logging.hpp"
#include "Texture.hpp"
#include "SDLTexture.hpp"

void* SDLRender::Init(IWindow *w) {
    
    SDLWindow* window = dynamic_cast<SDLWindow*>(w);
    
    if(window)
    {
        _render = SDL_CreateRenderer(window->GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED); //| SDL_RENDERER_TARGETTEXTURE);
    }
    else
    {
        LOG_ERROR("SDLRender::Init Window is empty");
        return nullptr;
    }
    
    LOG_MESSAGE("SDLRender::Init Render was created");
    return _render;
}

void SDLRender::Deinit() {
    if(_render)
    {
        SDL_DestroyRenderer(_render);
        _render = nullptr;
        LOG_MESSAGE("SDLRender::Deinit Render was destroyed");
    }
}

void SDLRender::Clear() {
    SDL_SetRenderDrawColor(_render, 0xA, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_render);
}

#include "Game.hpp"
#include "ResourceManager.hpp"
void SDLRender::Draw(Texture* texture, void* dst) {
    
    SDLTexture* txt = static_cast<SDLTexture*>(texture->resource);
    SDL_Rect* r_dst = static_cast<SDL_Rect*>(dst);
    SDL_RenderCopy(_render, txt->texture, &txt->src, r_dst);
}

void SDLRender::Present() { 
    SDL_RenderPresent(_render);
}

SDLRender::~SDLRender(){ 
    Deinit();
}

bool SDLRender::IsRenderExist() {
    return _render != nullptr;
}






