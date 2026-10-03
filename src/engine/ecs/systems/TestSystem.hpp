//
//  TestSystem.hpp
//  EPet
//
//  Created by marina porkhunova on 19.01.2025.
//

#ifndef TestSystem_hpp
#define TestSystem_hpp

#include "ISystem.hpp"

class TestSystem: public ISystem {
    SYSTEM_BODY(TestSystem)
    
public:
    void Init() override {};
    void DeInit() override {};
    void Update(double dt) override;
};

#endif /* TestSystem_hpp */
