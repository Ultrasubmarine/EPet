//
//  ISystem.hpp
//  EPet
//
//  Created by marina porkhunova on 08.01.2025.
//

#ifndef ISystem_hpp
#define ISystem_hpp

#include <stdio.h>
#include <iostream>

#define SYSTEM_BODY(CLASS_NAME) SYSTEM_CREATE_METHOD(CLASS_NAME)

/// Generating needed information to System in cpp.
/// @param CLASS_NAME - current class type
#define SYSTEM_CPP(CLASS_NAME) \
bool CLASS_NAME::c_register = REGISTER_SYSTEM_IN_FACTORY(CLASS_NAME);

/// Generating CreateMethod
/// @param CLASS_NAME - current class type
#define SYSTEM_CREATE_METHOD(CLASS_NAME) \
public: \
    static ISystem* CreateComponent() { return  new CLASS_NAME();} \
private: \
    static bool c_register;

#define REGISTER_SYSTEM_IN_FACTORY(CLASS_NAME) RegisterSystem(#CLASS_NAME, &CLASS_NAME::CreateComponent)

class ISystem{
public:
    virtual void Init() {};
    virtual void DeInit() {};
    virtual void Update() {};
    //save?
};

using TCreateSystem = ISystem*(*)();
bool RegisterSystem(const char* systemName, TCreateSystem createFunc);
#endif /* ISystem_hpp */
