//
//  ShellSystem.hpp
//  EPet
//
//  Created by marina porkhunova on 10.11.2026.
//

#ifndef ShellSystem_hpp
#define ShellSystem_hpp

#include "ISystem.hpp"

class ShellSystem: public ISystem {
    SYSTEM_BODY(ShellSystem)
    
public:
    void Init() override;
    void Update(double dt) override;
};

#endif // !ShellSystem_hpp
