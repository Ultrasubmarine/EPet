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
   // dt = 0.6666;
    for(auto [entt, animator, image] :_registry.view<Animator, Image>().each())
    {
   
        const auto entityCopy = entt;
        auto& anim = animator;
        auto& img = image;
        
        if(animator.timer >= animator.animation->_duration)
        {
            if(!animator.animation->_loop)
            {
                continue;
            }
            else
            {
                animator.timer = 0; // or animator.timer -= animator.animation->_duration ?
            }
        }
        
        double oneFrameTime = animator.animation->_duration / (animator.animation->_frames.size());
        
        int currentFrameIndex = animator.timer / oneFrameTime;
        currentFrameIndex = std::min(currentFrameIndex, static_cast<int>(animator.animation->_frames.size() - 1));
        
        SwitchFrame(entt, animator, image,currentFrameIndex);
        
        animator.timer += dt;
    }
    
}

void AnimationSystem::SwitchFrame(entt::entity, Animator& animator, Image& image, int frameIndex)
{
    if(image.resource == animator.animation->_frames[frameIndex])
    {
        return;
    }
    
    LOG_MESSAGE("Set animation frame"<< frameIndex<< " ["<< image.resoursesId<< "]");
    image.resource = animator.animation->_frames[frameIndex];
    image.resoursesId = animator.animation->_frames[frameIndex]->name;
    
    animator.frame = frameIndex;
}
