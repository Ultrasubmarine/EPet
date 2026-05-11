//
//  TextTexture.hpp
//  Labirint
//
//  Created by marina porkhunova on 26.02.2023.
//

#ifndef TextTexture_hpp
#define TextTexture_hpp

#include <stdio.h>
#include <string>

#include "SDLFont.h"
#include <SDL2/SDL.h>


struct SDLTextTexture
{
    SDL_Texture *texture;
    
    std::shared_ptr<SDLFont> font;
    std::string text;
    SDL_Color color;
    SDL_Rect rect;

    ~SDLTextTexture()
    {
        SDL_DestroyTexture(texture);
    }
    
    //no copy
    SDLTextTexture(const SDLTextTexture&) = delete;
    SDLTextTexture& operator=(const SDLTextTexture&) = delete;
    
    //no move
    SDLTextTexture(const SDLTextTexture&&) = delete;
    SDLTextTexture& operator=(const SDLTextTexture&&) = delete;
};

#endif /* TextTexture_hpp */
