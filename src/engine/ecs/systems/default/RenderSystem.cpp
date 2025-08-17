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

void RenderSystem::Update(double dt)
{
    auto view = _registry.view<Transform, Image>();
    
    _render->Clear();
    
    for(auto [entt, trasform, image] :_registry.view<Transform, Image>().each())
    {
       // image.resource
        _render->Draw(image.resource.get(), nullptr );
    }
    _render->Present();
}
