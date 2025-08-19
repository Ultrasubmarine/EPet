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

#include <SDL2/SDL.h>

#include "SDLTextureLoader.hpp"
#include "SDLRender.hpp"
#include "Game.hpp"

#include "SDLTexture.hpp"

std::shared_ptr<Texture> ITextureLoader::LoadTexture(const std::string& name, char *fullPath)
{
    if(auto resource = _LoadTexture(name, fullPath))
    {
        std::shared_ptr<Texture> texture{ resource, [this](Texture* t){ this->DeleteTexture(t);}};
        
        _textures[name] = std::weak_ptr<Texture>{texture};
        
        //it works
//        SDL_Rect f(10,10, 150,150);
//        auto ren = dynamic_cast<SDLRender*>(Game::Instance().GetRender());
//        
//        SDL_SetRenderDrawColor(ren->GetRender(), 0xFF, 0xA, 0xA, 0xFF);
//        SDL_RenderClear(ren->GetRender());
//        
//        SDLTexture* txt = static_cast<SDLTexture*>(resource->resource);
//        SDL_RenderCopy(ren->GetRender(), txt->texture, &f, &f);
//        
//       // SDL_RenderCopy(ren->GetRender(), bmpTex, &src, &f);
//        ren->Present();
        
        return texture;
    }
    
    LOG_ERROR("TextureLoader::LoadTexture() texture:"<<name);
    return NULL;
}
