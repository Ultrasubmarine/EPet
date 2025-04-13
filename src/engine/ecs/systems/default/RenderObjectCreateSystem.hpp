//
//  RenderObjectCreateSystem.hpp
//  EPet
//
//  Created by marina porkhunova on 13.04.2025.
//

#ifndef RenderObjectCreateSystem_hpp
#define RenderObjectCreateSystem_hpp

#include <stdio.h>
#include "ISystem.hpp"

class RenderObjectCreateSystem : public ISystem {
    SYSTEM_BODY(RenderObjectCreateSystem)
public:
    
    void Update(double dt) override;
};

#endif /* RenderObjectCreateSystem_hpp */
