//
//  RenderSystem.hpp
//  EPet
//
//  Created by marina porkhunova on 16.08.2025.
//

#ifndef RenderSystem_hpp
#define RenderSystem_hpp

#include <stdio.h>
#include "ISystem.hpp"

class IRender;

class RenderSystem: public ISystem {
    SYSTEM_BODY(RenderSystem)
    
public:
    void Init() override;
    void DeInit() override {};
    void Update(double dt) override;
    
private:
    IRender* _render;
};
#endif /* RenderSystem_hpp */
