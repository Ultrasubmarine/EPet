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

//TODO: move to .cpp file. 
#include "PointSerialization.hpp"

#include "json.hpp"
#include "Logging.hpp"

using json = nlohmann::json;
struct Texture;

struct TestComponent
{
    int value;
    std::string str;
    
    static TestComponent Load(const json& data)
    {
        TestComponent obj;
        
        obj.value = data["value"].get<int>();
        obj.str = data["str"].get<std::string>();
        
        return obj;
    }
    
    static void Save(TestComponent& obj, json& data)
    {
        data["value"] = obj.value;
        data["str"] = obj.str;
    }
};

struct Sorting
{
    int layer;
    static Sorting Load(const json& data)
    {
        Sorting obj;
        
        obj.layer= data["layer"].get<int>();
        
        return obj;
    }
    
    static void Save(Sorting& obj, json& data)
    {
        data["layer"] = obj.layer;
    }
};

struct Transform
{
    IPoint position = IPoint(0, 0);
    static Transform Load(const json& data);
//    {
//        Transform obj;
//        if(data.contains("position"))
//        {
//            obj.position = LoadPoint<int>(data["position"]);
//        }
//        
//        return obj;
//    }
    
    static void Save(Transform& obj, json& data);
//    {
//        json posData;
//        SavePoint<int>(obj.position, posData);
//        data["position"] = posData;
//    }
};

struct Image
{
    std::string resoursesId;
    std::shared_ptr<Texture> resource;
    
    static Image Load(const json& data);
//    {
//        Image obj;
//        if(data.contains("imageId"))
//        {
//            obj.resoursesId = data["imageId"].get<std::string>();
//        }
//        
//        //TODO: Load resource callback;
//    //    obj.resource = Game::Instance().GetResourceManager()->GetTexture(obj.resoursesId);
//        return obj;
//    }
    
    static void Save(Image& obj, json& data);
//    {
//        data["imageId"] = obj.resoursesId;
//    }
    
};
#endif /* CommonComponents_hpp */
