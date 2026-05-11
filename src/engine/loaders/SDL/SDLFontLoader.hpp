//
//  FontLoader.hpp
//  Labirint
//
//  Created by marina porkhunova on 25.02.2023.
//

#ifndef FontLoader_hpp
#define FontLoader_hpp

#include <stdio.h>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

#include "SDLFont.h"
#include "SDLTextTexture.hpp"

#include "IFontLoader.hpp"

class SDLRender;

class SDLFontLoader : public IFontLoader
{
    SDLRender* _render;
    
public:
    SDLFontLoader();
    virtual ~SDLFontLoader() override {};
    
protected:
    /// different libs could have different realisation for loading textures
    virtual Font* _LoadFont(const std::string& name, const char *fullPath) override;
};


#endif /* FontLoader_hpp */
