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

struct Texture
{
    std::string name;
    std::variant<SDLTexture*> resource;
    
    Texture(const std::string& name, SDLTexture* res): name(name), resource(res) {};
    
    ~Texture()
    {
        std::visit([](auto* r) { delete r;}, resource);
    }
    
    Texture(Texture& other) = delete;
    Texture& operator=(const Texture& other) = delete;
    
    Texture(Texture&& other) = delete;
    Texture& operator=(const Texture&& other) = delete;
    
};
#endif /* Texture_h */
