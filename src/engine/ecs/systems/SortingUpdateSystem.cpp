//  TextSystem.cpp
//  EPet
//
//  Создано по аналогии с RenderSystem.cpp
//

#include "SortingUpdateSystem.hpp"
#include "Game.hpp"
#include "IRender.h"
#include "ResourceManager.hpp"

SYSTEM_CPP(SortingUpdateSystem);

void SortingUpdateSystem::Init()
{
    UpdateObjectsSorting();
}

void SortingUpdateSystem::Update(double dt)
{
    if(_registry.view<UpdateSorting>().empty())
    {
        return;
    }
    
    UpdateObjectsSorting();
    _registry.clear<UpdateSorting>();
}

void SortingUpdateSystem::UpdateObjectsSorting()
{
    _registry.sort<Sorting>([](const auto &lhs, const auto &rhs) {
        return lhs.layer < rhs.layer;
    });
}
