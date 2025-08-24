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
    _render->Clear();
    
    auto view = _registry.view<Transform, Image>();
    for(auto [entt, trasform, image] :_registry.view<Transform, Image>().each())
    {
        SDL_Rect f(10,10, 150,150);
        _render->Draw(image.resource.get(), &f);
    }
    _render->Present();
}
