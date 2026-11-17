//
//  ImageLoadSystem.cpp
//  EPet
//
//  Created by marina porkhunova on 03.10.2026.
//

#include "ImageLoadSystem.hpp"
#include "Game.hpp"
#include "IRender.h"
#include "ResourceManager.hpp"

SYSTEM_CPP(ImageLoadSystem);

void ImageLoadSystem::Init()
{
    _resourceManager = Game::Instance().GetResourceManager();
    
    if(!_resourceManager)
    {
        return;
    }
    
    for(auto [entt, image, rObj] :_registry.view<Image, RendererObject>().each())
    {
        if(image.resoursesId.empty()) {
            continue;
        }
        
       // auto& rObj = _registry.emplace_or_replace<RendererObject>(entt);
        rObj.resource = _resourceManager->GetTexture(image.resoursesId);

    }
}

void ImageLoadSystem::Update(double dt)
{
}
