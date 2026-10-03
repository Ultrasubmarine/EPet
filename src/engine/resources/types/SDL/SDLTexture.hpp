//
//  SDLTexture.hpp
//  EPet
//
//  Created by marina porkhunova on 17.08.2025.
//

#ifndef SDLTexture_hpp
#define SDLTexture_hpp

#include <stdio.h>

#include <SDL2/SDL.h>
#include "SDLRender.hpp"

struct SDLTexture {
    
    SDL_Texture *texture;
    SDL_Rect src;
    
    SDLTexture(SDL_Texture* texture, SDL_Rect& src) : texture(texture), src(src) {};
    
    ~SDLTexture()
    {
        SDL_DestroyTexture(texture);
    }
    
    //no copy
    SDLTexture(const SDLTexture&) = delete;
    SDLTexture& operator=(const SDLTexture&) = delete;
    
    //no move
    SDLTexture(const SDLTexture&&) = delete;
    SDLTexture& operator=(const SDLTexture&&) = delete;
};
#endif /* SDLTexture_hpp */
