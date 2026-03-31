//
//  CommonComponents.hpp
//  EPet
//
//  Created by marina porkhunova on 27.01.2025.
//

#ifndef CommonComponents_hpp
#define CommonComponents_hpp

#include <stdio.h>
#include <iostream>

#include "Point.h"

#include "json.hpp"

using json = nlohmann::json;
struct Texture;

struct Sorting
{
    int layer;
    
    static Sorting Load(const json& data);
    static void Save(Sorting& obj, json& data);
};

struct Transform
{
    IPoint position = IPoint(0, 0);
    
    static Transform Load(const json& data);
    static void Save(Transform& obj, json& data);
};

struct Image
{
    std::string resoursesId;
    std::shared_ptr<Texture> resource;
    
    static Image Load(const json& data);
    static void Save(Image& obj, json& data);
};


struct Animation;

struct Animator
{
    std::string resoursesId;
    std::shared_ptr<const Animation> animation;
    
    double timer = 0;
    int frame = 0;
    
    double _oneFrameTime = 0; // calculated property!
    
    static Animator Load(const json& data);
    static void Save(Animator& obj, json& data);
};
#endif /* CommonComponents_hpp */
