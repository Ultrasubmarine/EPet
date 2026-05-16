//
//  FontLoader.hpp
//  Labirint
//
//  Created by marina porkhunova on 25.02.2023.
//

#ifndef SDLFontLoader_hpp
#define SDLFontLoader_hpp

#include <stdio.h>
#include "IFontLoader.hpp"

class SDLRender;

class SDLFontLoader : public IFontLoader
{
    SDLRender* _render;
    
public:
    SDLFontLoader();
    virtual ~SDLFontLoader() override {};
    
    virtual std::shared_ptr<Texture> GetTexture(std::string& text, std::shared_ptr<Font> font, const FontSettings& settings) override;
protected:

    /// different libs could have different realisation for loading textures
    virtual Font* _LoadFont(const std::string& name, const char *fullPath) override;

};

using FontLoader = SDLFontLoader;
#endif /* SDLFontLoader_hpp */
