//
//  SDLTextureLoader.hpp
//  EPet
//
//  Created by marina porkhunova on 11.04.2025.
//

#ifndef SDLTextureLoader_hpp
#define SDLTextureLoader_hpp

#include <stdio.h>
#include <string>

#include "ITextureLoader.hpp"

class SDLRender;
class Texture;

class SDLTextureLoader : public ITextureLoader
{
    SDLRender* _render;
    
public:
    SDLTextureLoader();
  
protected:
    Texture* _LoadTexture(const std::string& name, char *fullPath) override;
};

using TextureLoader = SDLTextureLoader;

#endif /* SDLTextureLoader_hpp */
