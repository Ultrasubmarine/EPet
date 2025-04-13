//
//  TextureLoader.hpp
//  Labirint
//
//  Created by marina porkhunova on 07.01.2023.
//

#ifndef TextureLoader_hpp
#define TextureLoader_hpp

#include <memory>
#include <string>
#include <stdio.h>
#include <unordered_map>

#include "Texture.hpp"

class Texture;

class ITextureLoader
{
protected:
    std::unordered_map<std::string, std::weak_ptr<Texture>> _textures;
    
public:
    ITextureLoader() = default;
    virtual ~ITextureLoader();
    
    std::shared_ptr<Texture> GetTexture(std::string& name);
    std::shared_ptr<Texture> LoadTexture(std::string& name, char *fullPath);
    
protected:
    void DeleteTexture(Texture* texture);
    
    /// different libs could have different realisation for loading textures
    virtual Texture* _LoadTexture(std::string& name, char *fullPath) = 0;
};

#endif /* TextureLoader_hpp */
