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

SYSTEM_CPP(RenderSystem);

void RenderSystem::Init()
{
    _render = Game::Instance().GetRender();
}

void RenderSystem::Update(double dt)
{
    _render->Clear();
    
    auto view = _registry.view<Transform, Image>();
    for(auto [entt, trasform, image] :_registry.view<Transform, Image>().each())
    {
        _render->Draw(image.resource.get(), trasform.position.x, trasform.position.y);
    }
    _render->Present();
}
