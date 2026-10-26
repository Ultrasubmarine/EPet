//
//  HamsterGame.cpp
//  EPet
//
//  Created by marina porkhunova on 23.09.2026.
//

#include "HamsterGame.hpp"

#include "ResourceManager.hpp"
#include "RegisterHamsterComponents.hpp"

#include "Logger.hpp"

bool HamsterGame::Init(ResourceManager* resourceManager)
{
    if (!resourceManager)
    {
        LOG_ERROR("Resource manager is null");
        return false;
    }

    if (auto manifest = resourceManager->GetJson("hamster_animations", ResourceType::settings))
    {
        _animationDictionary.Load(resourceManager, manifest.get());
    }
    else
    {
        LOG_ERROR("Animation manifest [hamster_animations.json] not loaded");
        return false;
    }
    
    RegisterHamsterComponents();
    return true;
}
