//
//  AnimationSystem.hpp
//  EPet
//
//  Created by marina porkhunova on 12.03.2026.
//

#ifndef AnimationSystems_hpp
#define AnimationSystems_hpp

#include <stdio.h>
#include "ISystem.hpp"

struct Animator;
struct Image;
struct RendererObject;

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
#endif /* AnimationSystems_hpp */
