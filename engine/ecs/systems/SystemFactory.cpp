//
//  SystemFactory.cpp
//  EPet
//
//  Created by marina porkhunova on 08.01.2025.
//

#include "SystemFactory.hpp"

#define REGISTER(CLASS_NAME) #CLASS_NAME, &CLASS_NAME::CreateSystem

//void SystemFactory::RegistrySystems()
//{
//    Register("TestSystem", &TestSystem::CreateSystem);
//}
