//
//  ISystem.cpp
//  EPet
//
//  Created by marina porkhunova on 08.01.2025.
//

#include "ISystem.hpp"
#include "SystemFactory.hpp"

bool RegisterSystem(const char* systemName, TCreateSystem createFunc)
{
    return SystemFactory::Instance().Register(systemName, createFunc);
}
