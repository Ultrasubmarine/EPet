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
    
    // TODO: move it in different system
    _registry.sort<Sorting>([](const auto &lhs, const auto &rhs) {
        return lhs.layer < rhs.layer;
    });
    //-----------------------------------
}

void RenderSystem::Update(double dt)
{
    _render->Clear();
    
    for(auto [entt, _, trasform, image] :_registry.view<Sorting, Transform, Image>().each())
    {
        _render->Draw(image.resource.get(), trasform.position.x, trasform.position.y);
    }
    
    _render->Present();
}
