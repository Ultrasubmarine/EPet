//
//  Texture.h
//  EPet
//
//  Created by marina porkhunova on 03.08.2024.
//

#ifndef Texture_h
#define Texture_h

#include <functional>

//TODO: 5th rule, please
struct Texture
{
    std::string name;
    
    // cast it for speciphic graphic libs structures. SDLTexture or etc.
    void* resource;
    std::function<void(void*)> deleter; // function that destroy resource
    
    ~Texture()
    {
        deleter(resource);
    }
};
#endif /* Texture_h */
