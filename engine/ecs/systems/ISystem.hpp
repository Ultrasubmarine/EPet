//
//  ISystem.hpp
//  EPet
//
//  Created by marina porkhunova on 08.01.2025.
//

#ifndef ISystem_hpp
#define ISystem_hpp

#include <stdio.h>

//#define BASE_SYSTEM_CLASS_NAME ISystem
//
//#define REGISTER_INIT(CLASS_NAME) \
//( &CLASS_NAME::Draw != &DEFAULT_COMPONENT_VALUE::Draw) ? RegisterDraw(TYPE_ID(CLASS_NAME)) : true
//
//#define REGISTER_DEINIT(CLASS_NAME) \
//( &CLASS_NAME::Draw != &DEFAULT_COMPONENT_VALUE::Draw) ? RegisterDraw(TYPE_ID(CLASS_NAME)) : true
//
//
///// Generating CreateMethod
//#define SYSTEM_CREATE_METHOD(CLASS_NAME) \
//public: \
//    static ISystem* CreateComponent() { return  new CLASS_NAME(id);} \
//private: \
//    static bool c_register;
//
//
//#define SYSTEM_CPP(CLASS_NAME) \
// 
//
/////
//#define REGISTER_SYSTEM_IN_FACTORY(CLASS_NAME) RegisterComponent( #CLASS_NAME, &CLASS_NAME::CreateComponent)

class ISystem{
public:
    virtual void Init() {};
    virtual void DeInit() {};
    virtual void Update() {};
    //save?
};

//using TCreateSystem = ISystem*(*)();
//bool RegisterSystem(const char *componentName, TCreateSystem createFunc);


class TestSystem: public ISystem{
    
public:
    void Init() override {};
    void DeInit() override {};
    void Update() override {};
    
public:
    static ISystem* CreateSystem() { return  new TestSystem();}
private:
   
};
#endif /* ISystem_hpp */
