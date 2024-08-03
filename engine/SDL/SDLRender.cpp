//
//  SDLRender.cpp
//  EPet
//
//  Created by marina porkhunova on 03.08.2024.
//

#include "SDLRender.hpp"

#include <SDL2/SDL.h>
#include "SDLWindow.h"

void SDLRender::Clear() {
    SDL_SetRenderDrawColor(_render, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_render);
}

void SDLRender::Init(IWindow *w) { 
    
    SDLWindow* window = dynamic_cast<SDLWindow*>(w);
    
    if(window)
    {
        _render = SDL_CreateRenderer(window->GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED); //| SDL_RENDERER_TARGETTEXTURE);
    }
    else
    {
        //error
    }
    
}

void SDLRender::Draw(Rect& source, Rect& windRect) { 
  //  SDL_RenderCopy(_render, nullptr/*_texture->texture */, static_cast<SDL_Rect>(source), static_cast<SDL_Rect>(windRect);
}

void SDLRender::Present() { 
    SDL_RenderPresent(_render);
}

SDLRender::~SDLRender(){ 
    SDL_DestroyRenderer(_render);
}






