//
//  AnimationSystem.hpp
//  EPet
//
//  Created by marina porkhunova on 12.03.2026.
//

#ifndef AnimationSystems_hpp
#define AnimationSystems_hpp

#include <stdio.h>
#include <memory>
#include "ISystem.hpp"

struct Animator;
struct Image;
struct RendererObject;
struct Animation;


class AnimationUpdateSystem: public ISystem {
    SYSTEM_BODY(AnimationUpdateSystem)
    
public:
    void Update(double dt) override;
    
private:
    
    void SwitchFrame(entt::entity, Animator& animator, RendererObject& rObj, Image& image, int frameIndex) const;
    int CalculateCurrentFrame(entt::entity, Animator& animator) const;
    void FinishAnimation(entt::entity, Animator& animator) const;
    
    void ClearOneFrameComponents() const;
};



class AnimationFinishSystem: public ISystem {
    SYSTEM_BODY(AnimationFinishSystem)
    
public:
    void Update(double dt) override;
};


class AnimationSwitchSystem: public ISystem {
    SYSTEM_BODY(AnimationSwitchSystem)
    
public:
    void Update(double dt) override;
    
private:
    void ChangeAnimation(entt::entity, std::shared_ptr<const Animation> newAnimation, Animator& animator);

};
#endif /* AnimationSystems_hpp */
