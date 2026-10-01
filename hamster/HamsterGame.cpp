//
//  HamsterGame.cpp
//  EPet
//
//  Created by marina porkhunova on 23.09.2026.
//

#include "HamsterGame.hpp"

#include "ResourceManager.hpp"
#include "Logging.hpp"

void HamsterGame::Init(ResourceManager* resourceManager)
{
    if (!resourceManager)
    {
        LOG_ERROR("empty ResourceManager");
        return;
    }

    if (auto manifest = resourceManager->GetJson("hamster_animations", ResourceType::settings))
    {
        _animationDictionary.Load(resourceManager, manifest);
    }
    else
    {
        LOG_ERROR("hamster_animations.json didn't load");
    }
}
