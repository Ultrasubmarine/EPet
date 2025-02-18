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
#include "registry.hpp"
#include "json.hpp"
#include "FactoryMethod.hpp"
using json = nlohmann::json;


struct TestComponent
{
    int value;
    std::string str = "hello, my friends";
    static TestComponent Load(const json& data)
    {
        TestComponent obj;
        
        obj.value = data["value"].get<int>();
        
        return obj;
    }
    
    static void Save(TestComponent& obj, json& data)
    {
        data["value"] = obj.value;
        data["str"] = obj.str;
    }
};

class ComponentRegister
{
public:
    using alizeFunction = void(*)(json*);
    using creationFunction = void(*)(entt::registry&, entt::entity);
private:
    std::map<std::string, alizeFunction> _loadFunctions;
    std::map<std::string, alizeFunction> _saveFunctions;
    
    std::map<std::string, creationFunction> _createFunctions;
    
public:
    void Register(std::string& name, alizeFunction loadFunction, alizeFunction saveFunction)
    {
        _loadFunctions[name] = loadFunction;
        _saveFunctions[name] = saveFunction;
    };
    
    alizeFunction GetLoadFunction(std::string& name)
    {
        if(auto it = _loadFunctions.find(name); it != _loadFunctions.end())
        {
            return it->second;
        }
        return nullptr;
    }
    
    //test functions for undarstanding
    // TODO: fix string without reference
    void Register(std::string name, creationFunction createFunction)
    {
        _createFunctions[name] = createFunction;
    };
    
    creationFunction GetCreateFunction(std::string& name)
    {
        if(auto it = _createFunctions.find(name); it != _createFunctions.end())
        {
            return it->second;
        }
        return nullptr;
    }
};

//template<typename T>
//void loadFunction(ComponentRegister componentRegister, entt::registry& registry, std::string name, entt::entity entity, json* data)
//{
//    registry.emplace<T>(entity);
//    
//    componentRegister.GetLoadFunction(name);
//    _map[name](data);
//}
#endif /* CommonComponents_hpp */
