//
//  RenderSystem.cpp
//  EPet
//
//  Created by marina porkhunova on 16.08.2025.
//

#include "RenderSystem.hpp"
#include "CommonComponents.hpp"

#include "Game.hpp"
#include "IRender.h"
#include "Texture.hpp"

SYSTEM_CPP(RenderSystem);

void RenderSystem::Init()
{
    _render = Game::Instance().GetRender();
}


#include <SDL2/SDL.h>

#include "SDLTextureLoader.hpp"
#include "SDLRender.hpp"
#include "Game.hpp"

#include "SDLTexture.hpp"

void RenderSystem::Update(double dt)
{
    auto view = _registry.view<Transform, Image>();
    
    _render->Clear();
    auto ren = dynamic_cast<SDLRender*>(Game::Instance().GetRender());
    
    for(auto [entt, trasform, image] :_registry.view<Transform, Image>().each())
    {
        SDL_Rect f(10,10, 150,150);

        SDLTexture* txt = static_cast<SDLTexture*>(image.resource->resource);
        SDL_RenderCopy(ren->GetRender(), txt->texture, &f, &f);
        
        _render->Draw(image.resource, &f);
       // SDL_RenderCopy(ren->GetRender(), bmpTex, &src, &f);
    }
    _render->Present();
}
