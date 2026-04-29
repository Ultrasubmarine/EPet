//
//  AnimationSystem.cpp
//  EPet
//
//  Created by marina porkhunova on 12.03.2026.
//

#include "AnimationSystems.hpp"
#include "CommonComponents.hpp"

#include "Animation.hpp"
#include "Texture.hpp"
#include "Logging.hpp"

SYSTEM_CPP(AnimationUpdateSystem);
SYSTEM_CPP(AnimationFinishSystem);

void AnimationUpdateSystem::Update(double dt)
{
    ClearOneFrameComponents();
    
    for(auto [entt, animator, image] :_registry.view<Animator, Image>(entt::exclude<AnimationFinished>).each())
    {
        
        if(animator.timer >= animator.animation->_duration)
        {
            if(!animator.animation->_loop)
            {
                FinishAnimation(entt, animator);
                continue;
            }
            else // refresh timer
            {
                animator.timer = std::fmod(animator.timer, animator.animation->_duration);
            }
        }
        
        if(animator.animation->_frames.empty())
        {
            LOG_ERROR("AnimationSystem::Update() animation ["<<animator.animation->_name<<"] doesn't have any frames");
            FinishAnimation(entt, animator);
            return;
        }
        
        int currentFrameIndex = CalculateCurrentFrame(entt, animator);
        SwitchFrame(entt, animator, image,currentFrameIndex);
        
        animator.timer += dt;
    }
    
}

void AnimationUpdateSystem::ClearOneFrameComponents() const
{
    _registry.clear<AnimationFinished_OF>();
}

int AnimationUpdateSystem::CalculateCurrentFrame(entt::entity, Animator& animator) const
{
    int currentFrameIndex = 0;
    switch (animator.animation->_mode) {
        case PlayMode::Forward:
        {
            currentFrameIndex = animator.timer / animator.animation->_oneFrameTime;
            break;
        }
        case PlayMode::Reverse:
        {
            currentFrameIndex = (animator.animation->_duration - animator.timer)/ animator.animation->_oneFrameTime;
            break;
        }
        case PlayMode::YoYo:
        {
            if(animator.timer < animator.animation->_duration/2) // as forward
            {
                currentFrameIndex = animator.timer / animator.animation->_oneFrameTime;
                break;
            }
            else // as reverse
            {
                currentFrameIndex = (animator.animation->_duration - animator.timer)/ animator.animation->_oneFrameTime;
                break;
            }
        }
        default:
            break;
    }

    currentFrameIndex = std::max(0, std::min(currentFrameIndex, static_cast<int>(animator.animation->_frames.size() - 1)));
    return currentFrameIndex;
}

void AnimationUpdateSystem::SwitchFrame(entt::entity, Animator& animator, Image& image, int frameIndex) const
{
    if(image.resource == animator.animation->_frames[frameIndex])
    {
        return;
    }
    
    LOG_MESSAGE("AnimationSystem::SwitchFrame() Set animation frame"<< frameIndex<< " ["<< image.resoursesId<< "]");
    image.resource = animator.animation->_frames[frameIndex];
    image.resoursesId = animator.animation->_frames[frameIndex]->name;
    
    animator.frame = frameIndex;
}

void AnimationUpdateSystem::FinishAnimation(entt::entity ent, Animator& animator) const
{
    _registry.emplace_or_replace<AnimationFinished_OF>(ent, animator.resoursesId);
}





// FINISH ANIMATION
void AnimationFinishSystem::Update(double)
{
    for(auto [entt, animator, _ ] :_registry.view<Animator, AnimationFinished_OF>().each())
    {
        //mark us finished
        _registry.emplace_or_replace<AnimationFinished>(entt, animator.resoursesId);
    }
}
