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

void RenderSystem::Start()
{
    _render = Game::Instance().GetRender();
}

void RenderSystem::Update(double dt)
{
    _render->Clear();

    auto view = _registry.view<Sorting, Transform, RendererObject>();
    view.use<Sorting>();
    
    for(auto [entity, _, transform, rObj] : view.each())
    {
        const auto* pivot = _registry.try_get<Pivot>(entity);
        _render->Draw(rObj.resource.get(), transform.position.x, transform.position.y, pivot ? pivot->point : Pivot::TopLeft);
    }
    
    _render->Present();
}
