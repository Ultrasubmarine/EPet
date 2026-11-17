//
//  SortingSystem.cpp
//  EPet
//
//  Created by marina porkhunova on 03.10.2026.
//

#include "SortingSystem.hpp"
#include "Game.hpp"
#include "IRender.h"
#include "ResourceManager.hpp"

SYSTEM_CPP(SortingSystem);

void SortingSystem::Init()
{
    _registry.on_construct<Sorting>().connect<&SortingSystem::OnSortingChanged>(this);
    _registry.on_destroy<Sorting>().connect<&SortingSystem::OnSortingChanged>(this);
    
    // components are bound with Sorting component
    _registry.on_construct<Image>().connect<&SortingSystem::OnSpecialComponentAdded>(this);
    _registry.on_construct<Text>().connect<&SortingSystem::OnSpecialComponentAdded>(this);
    
    UpdateObjectsSorting();
}

void SortingSystem::DeInit()
{
    _registry.on_construct<Sorting>().disconnect<&SortingSystem::OnSortingChanged>(this);
    _registry.on_destroy<Sorting>().disconnect<&SortingSystem::OnSortingChanged>(this);
    
    _registry.on_construct<Image>().disconnect<&SortingSystem::OnSpecialComponentAdded>(this);
    _registry.on_construct<Text>().disconnect<&SortingSystem::OnSpecialComponentAdded>(this);
}

void SortingSystem::Update(double dt)
{
    if(auto* state = _registry.ctx().find<SortingState>(); state && state->dirty)
    {
        UpdateObjectsSorting();
        _registry.ctx().insert_or_assign(SortingState{false});
    }
}

void SortingSystem::UpdateObjectsSorting()
{
    _registry.sort<Sorting>([](const auto &lhs, const auto &rhs) {
        return lhs.GetLayer() < rhs.GetLayer();
    });
}

void SortingSystem::OnSortingChanged(entt::registry& registry, entt::entity entity)
{
    _registry.ctx().insert_or_assign(SortingState{true});
}

void SortingSystem::OnSpecialComponentAdded(entt::registry& registry, entt::entity entity)
{
    if(!_registry.try_get<Sorting>(entity))
    {
        _registry.emplace<Sorting>(entity, 0);
    }
}
