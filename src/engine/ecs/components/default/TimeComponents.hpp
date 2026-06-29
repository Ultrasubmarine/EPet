//
//  CommonComponents.hpp
//  EPet
//
//  Created by marina porkhunova on 27.01.2025.
//

#ifndef TimeComponents_hpp
#define TimeComponents_hpp

#include <stdio.h>
#include <iostream>

#include "registry.hpp"

//#include "json.hpp"
//
//using json = nlohmann::json;


//struct Transform
//{
//    IPoint position = IPoint(0, 0);
//    
//    static Transform Load(const json& data);
//    static void Save(Transform& obj, json& data);
//};
//
//
//
//struct AnimationFinished_OF /// one shot
//{
//    std::string resoursesId;
//};

struct Timer
{
    double timeLeft;
    double duration;
};

struct TimerFinished_OF /// one shot
{
};

struct TimerFinished
{
};

/// arg duration - in seconds. 
/// true - if creating is succesefull
bool CreateTimer(double duration, entt::entity* outCreatedEntity = nullptr, Timer* outCreatedTimer = nullptr);


#endif /* TimeComponents_hpp */
