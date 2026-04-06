//
//  AnimationSystem.hpp
//  EPet
//
//  Created by marina porkhunova on 12.03.2026.
//

#ifndef AnimationSystem_hpp
#define AnimationSystem_hpp

#include <stdio.h>
#include "ISystem.hpp"

struct Animator;
struct Image;

class AnimationSystem: public ISystem {
    SYSTEM_BODY(AnimationSystem)
    
public:
    void Init() override;
    void DeInit() override {};
    void Update(double dt) override;
    
private:
    
    void SwitchFrame(entt::entity, Animator& animator, Image& image, int frameIndex) const;
    int CalculateCurrentFrame(entt::entity, Animator& animator) const;
};
#endif /* AnimationSystem_hpp */
