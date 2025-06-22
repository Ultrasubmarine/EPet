//
//  TextureLoader.cpp
//  Labirint
//
//  Created by marina porkhunova on 07.01.2023.
//

#include "ITextureLoader.hpp"

#include <string>

#include "Logging.hpp"

void ITextureLoader::DeleteTexture(Texture* texture)
{
    _textures.erase(texture->name);
    delete texture;
}

std::shared_ptr<Texture> ITextureLoader::GetTexture(const std::string& name)
{
    if(auto it = _textures.find(name); it != _textures.end())
        return it->second.lock() ;
    
    return nullptr;
}

ITextureLoader::~ITextureLoader()
{
    _textures.clear();
}

std::shared_ptr<Texture> ITextureLoader::LoadTexture(const std::string& name, char *fullPath)
{
    if(auto resource = _LoadTexture(name, fullPath))
    {
        std::shared_ptr<Texture> texture{ resource, [this](Texture* t){ this->DeleteTexture(t);}};
        
        _textures[name] = std::weak_ptr<Texture>{texture};
        return texture;
    }
    
    LOG_ERROR("TextureLoader::LoadTexture() texture:"<<name);
    return NULL;
}
