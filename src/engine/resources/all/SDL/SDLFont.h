//
//  Font.h
//  Labirint
//
//  Created by marina porkhunova on 07.04.2023.
//

#ifndef Font_h
#define Font_h

#include <string>
#include <SDL2_ttf/SDL_ttf.h>

struct SDLFont
{
    TTF_Font *font;

    SDLFont(TTF_Font *res) : font(res) {};
    ~SDLFont()
    {
        TTF_CloseFont(font);
    }
    
    //no copy
    SDLFont(const SDLFont&) = delete;
    SDLFont& operator=(const SDLFont&) = delete;
    
    //no move
    SDLFont(const SDLFont&&) = delete;
    SDLFont& operator=(const SDLFont&&) = delete;
};

#endif /* Font_h */
