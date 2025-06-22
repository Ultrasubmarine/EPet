//
//  SystemFactory.hpp
//  EPet
//
//  Created by marina porkhunova on 08.01.2025.
//

#ifndef SystemFactory_hpp
#define SystemFactory_hpp

#include <stdio.h>
#include "FactoryMethod.hpp"
#include "Singleton.hpp"
#include "ISystem.hpp"

#include "registry.hpp"

class SystemFactory : public FactoryMethod<std::string, ISystem, entt::registry&>, public Singleton<SystemFactory>
{
};

#endif /* SystemFactory_hpp */
