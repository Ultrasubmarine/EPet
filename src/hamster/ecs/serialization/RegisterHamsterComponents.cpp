//
//  RegisterHamsterComponents.cpp
//  EPet
//
//  Created by marina porkhunova on 05.10.2026.
//

#include "RegisterHamsterComponents.hpp"

#include "LoadComponents.hpp"

#include "HM_AvatarComponents.hpp"

void RegisterHamsterComponents()
{
    GenerateLoadingFunction<Avatar>("Avatar", &Avatar::Load);
}
