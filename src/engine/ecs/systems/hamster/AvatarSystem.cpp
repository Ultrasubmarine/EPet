//
//  AvatarSystem.cpp
//  EPet
//
//  Created by marina porkhunova on 23.09.2026.
//

#include "AvatarSystem.hpp"

#include "HM_StatesComponents.hpp"
#include "HM_AvatarComponents.hpp"

#include "CommonComponents.hpp"

#include "Game.hpp"
#include "HamsterGame.hpp"

#include "PlayerSave.hpp"
#include "Logging.hpp"

SYSTEM_CPP(AvatarSystem);

void AvatarSystem::Init()
{
    if(!_registry.storage<Avatar>().empty())
    {
       UpdateAvatar();
    }
    else
    {
        LOG_MESSAGE("Avatar doesn't exist on scene.");
    }
}

void AvatarSystem::Update(double dt)
{
    if(!_registry.storage<LevelChanged_OF>().empty())
    {
        UpdateAvatar();
    }
}

bool AvatarSystem::UpdateAvatar()
{
    for(auto [ent, level] : _registry.view<Level>().each())
    {
        auto l = level.value;
        auto tag = RecalculateTag();
        
        auto animation = HamsterGame::Instance().GetAnimationDictionary().Get(l, tag);
        
        
        // set on scene
        auto view = _registry.view<Avatar, Animator>();
        auto entity = view.front();
        if (entity == entt::null) {
            return false;
        }
        auto [avatar, animator] = view.get<Avatar, Animator>(entity);
        _registry.emplace_or_replace<SwitchAnimation>(entity, animation);
    }
    return false;
}

std::string AvatarSystem::RecalculateTag()
{
    return "normal"; // tmp
}



