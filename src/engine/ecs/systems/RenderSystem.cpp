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
    
    //without sorting
//    for(auto [entt, trasform, rObj] :_registry.view<Transform, RendererObject>(entt::exclude<Sorting>).each())
//    {
//        _render->Draw(rObj.resource.get(), trasform.position.x, trasform.position.y);
//    }
    //auto fff = _registry.view<Sorting, Transform, RendererObject>();
    
    for(auto [entt, _, trasform, rObj] :_registry.view<Sorting, Transform, RendererObject>().each())
    {
        _render->Draw(rObj.resource.get(), trasform.position.x, trasform.position.y);
    }
    
    _render->Present();
}
