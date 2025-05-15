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

#include "json.hpp"
using json = nlohmann::json;

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

class RenderObject;

struct Image
{
    std::string resourses_id;
    std::unique_ptr<RenderObject> resource;
};
#endif /* CommonComponents_hpp */
