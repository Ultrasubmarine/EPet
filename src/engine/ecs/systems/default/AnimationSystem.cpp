//
//  AnimationSystem.cpp
//  EPet
//
//  Created by marina porkhunova on 12.03.2026.
//

#include "AnimationSystem.hpp"
#include "CommonComponents.hpp"

#include "Animation.hpp"
#include "Texture.hpp"
#include "Logging.hpp"

SYSTEM_CPP(AnimationSystem);

void AnimationSystem::Init()
{};

void AnimationSystem::Update(double dt)
{
    for(auto [entt, animator, image] :_registry.view<Animator, Image>().each())
    {
        if(animator.timer >= animator.animation->_duration)
        {
            if(!animator.animation->_loop)
            {
                continue;
            }
            else
            {
                animator.timer = std::fmod(animator.timer, animator.animation->_duration);
            }
        }
        
        int currentFrameIndex = animator.timer / animator.animation->_oneFrameTime;
        currentFrameIndex = std::max(0, std::min(currentFrameIndex, static_cast<int>(animator.animation->_frames.size() - 1)));
        
        SwitchFrame(entt, animator, image,currentFrameIndex);
        animator.timer += dt;
    }
    
}

void AnimationSystem::SwitchFrame(entt::entity, Animator& animator, Image& image, int frameIndex)
{
    if(animator.animation->_frames.empty())
    {
        LOG_ERROR("AnimationSystem::SwitchFrame() animation ["<<animator.animation->_name<<"] doesn't have any frames");
        return;
    }
    
    if(image.resource == animator.animation->_frames[frameIndex])
    {
        return;
    }
    
    LOG_MESSAGE("AnimationSystem::SwitchFrame() Set animation frame"<< frameIndex<< " ["<< image.resoursesId<< "]");
    image.resource = animator.animation->_frames[frameIndex];
    image.resoursesId = animator.animation->_frames[frameIndex]->name;
    
    animator.frame = frameIndex;
}
