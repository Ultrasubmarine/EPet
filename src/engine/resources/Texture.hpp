//
//  Texture.h
//  EPet
//
//  Created by marina porkhunova on 03.08.2024.
//

#ifndef Texture_h
#define Texture_h

#include <variant>
#include <functional>

struct SDLTexture;

//TODO: 5th rule, please
struct Texture
{
    std::string name;
    std::variant<SDLTexture*> resource;
    
    ~Texture()
    {
        std::visit([](auto* r) { delete r;}, resource);
    }
};
#endif /* Texture_h */
