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
#include "Logger.hpp"

SYSTEM_CPP(ImageLoadSystem);

void ImageLoadSystem::OnSystemsLoaded()
{
    _registry.on_construct<Image>().connect<&ImageLoadSystem::OnImageChanged>(this);
    _registry.on_update<Image>().connect<&ImageLoadSystem::OnImageChanged>(this);
}

void ImageLoadSystem::DeInit()
{
    _registry.on_construct<Image>().disconnect<&ImageLoadSystem::OnImageChanged>(this);
    _registry.on_update<Image>().disconnect<&ImageLoadSystem::OnImageChanged>(this);
}

void ImageLoadSystem::OnImageChanged(entt::registry& registry, entt::entity entity)
{
    _registry.emplace_or_replace<UpdateImage>(entity);
}

void ImageLoadSystem::Start()
{
    _resourceManager = Game::Instance().GetResourceManager();
    if(!_resourceManager)
    {
        LOG_ERROR("Resource manager is null. Images will not be loaded");
    }
}

void ImageLoadSystem::Update(double dt)
{
    if(!_resourceManager)
    {
        return;
    }
    
    for(auto [entt, image, rObj] :_registry.view<Image, RendererObject, UpdateImage>().each())
    {
        LoadImage(image,rObj);
        _registry.remove<UpdateImage>(entt);
    }
}

void ImageLoadSystem::LoadImage(Image& image, RendererObject& obj)
{
    if(image.GetImageId().empty()) {
        LOG_MESSAGE("Image id is empty. Texture cleared");
        obj.resource = nullptr;
        return;
    }
    
    obj.resource = _resourceManager->GetTexture(image.GetImageId());
}
