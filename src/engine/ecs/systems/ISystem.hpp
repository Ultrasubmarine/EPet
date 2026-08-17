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
#include "registry.hpp" // TODO: think about place

/// @param CLASS_NAME - current class type
/// @param ... - initializers for extra base classes, if any. Use "registry" as the ctor arg name.
///              example: SYSTEM_BODY(GrowingSystem, Ticker(registry))
#define SYSTEM_BODY(CLASS_NAME, ...) SYSTEM_CREATE_METHOD(CLASS_NAME __VA_OPT__(,) __VA_ARGS__)

/// Generating needed information to System in cpp.
/// @param CLASS_NAME - current class type
#define SYSTEM_CPP(CLASS_NAME) \
bool CLASS_NAME::c_register = REGISTER_SYSTEM_IN_FACTORY(CLASS_NAME);

/// Generating CreateMethod
/// @param CLASS_NAME - current class type
/// @param ... - initializers for extra base classes
#define SYSTEM_CREATE_METHOD(CLASS_NAME, ...) \
public: \
    static ISystem* CreateComponent(entt::registry& registry) { return  new CLASS_NAME(registry);}; \
    CLASS_NAME(entt::registry& registry) : ISystem(registry) __VA_OPT__(,) __VA_ARGS__ {}; \
    const char* GetSystemId() const override { return #CLASS_NAME; }; \
private: \
    static bool c_register;


#define REGISTER_SYSTEM_IN_FACTORY(CLASS_NAME) RegisterSystem(#CLASS_NAME, &CLASS_NAME::CreateComponent)

class ISystem{
    
public:
    ISystem(entt::registry& registry) : _registry(registry) {};
    virtual ~ISystem() {};
    
    virtual void Init() {};
    virtual void DeInit() {};
    virtual void Update(double dt) {};
    virtual const char*  GetSystemId() const { return "ISystem";};
protected:
    entt::registry& _registry;
};

using TCreateSystem = ISystem*(*)(entt::registry& registry);
bool RegisterSystem(const char* systemName, TCreateSystem createFunc);

#endif /* ISystem_hpp */
