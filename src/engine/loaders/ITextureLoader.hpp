//
//  TextureLoader.hpp
//  Labirint
//
//  Created by marina porkhunova on 07.01.2023.
//

#ifndef TextureLoader_hpp
#define TextureLoader_hpp

#include <stdio.h>
#include <memory>
#include <unordered_map>

#include "Texture.hpp"

class ITextureLoader
{
protected:
    std::unordered_map<std::string, std::weak_ptr<Texture>> _textures;
    
public:
    ITextureLoader() = default;
    virtual ~ITextureLoader();
    
    std::shared_ptr<Texture> GetTexture(const std::string& name);
    std::shared_ptr<Texture> LoadTexture(const std::string& name, const char *fullPath);
    
protected:
    /// different libs could have different realisation for loading textures
    virtual Texture* _LoadTexture(const std::string& name, const char *fullPath) = 0;
    
    void DeleteTexture(Texture* texture);
};

#endif /* TextureLoader_hpp */
