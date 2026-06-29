//
//  CommonComponents.cpp
//  EPet
//
//  Created by marina porkhunova on 07.07.2025.
//

#include <stdio.h>

#include "TimeComponents.hpp"

#include "Game.hpp"
#include "SceneManager.hpp"

#include "Logging.hpp"
#include "registry.hpp"

/// true - if creating is succesefull
bool CreateTimer(double duration, entt::entity* outCreatedEntity, Timer* outCreatedTimer)
{
    static auto& _registry = Game::Instance().GetSceneManager()->GetRegistry();
    
    auto ent = _registry.create();
    if(ent == entt::null)
    {
        outCreatedEntity = nullptr;
        outCreatedTimer = nullptr;
        return false;
    }
    
    auto component = _registry.emplace<Timer>(ent, duration, duration);
    
    if(outCreatedTimer)
    {
        *outCreatedTimer = component;
    }
    if(outCreatedEntity)
    {
        *outCreatedEntity = static_cast<entt::entity>(ent);
    }
    
    return true;
}
