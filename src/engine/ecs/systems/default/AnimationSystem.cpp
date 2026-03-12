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

SYSTEM_CPP(AnimationSystem);

void AnimationSystem::Init()
{};

void AnimationSystem::Update(double dt)
{
    
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
        animator.timer += dt;
        
        double oneFrameTime = animator.animation->_duration / animator.animation->_frames.size();
        
        int currentFrameTime = animator.timer / oneFrameTime;
        currentFrameTime = std::min(currentFrameTime, static_cast<int>(animator.animation->_frames.size() - 1));
        
        SwitchFrame(entt, animator, image,currentFrameTime);
        
    }
    
}

void AnimationSystem::SwitchFrame(entt::entity, Animator& animator, Image& image, int frameIndex)
{
    image.resource = animator.animation->_frames[frameIndex];
    image.resoursesId = animator.animation->_frames[frameIndex]->name;
    
    animator.frame = frameIndex;
}
