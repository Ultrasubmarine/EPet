//
//  SaveLoadComponents.hpp
//  EPet
//
//  Created by marina porkhunova on 09.02.2025.
//

#ifndef SaveLoadComponents_hpp
#define SaveLoadComponents_hpp

#include <stdio.h>
#include <string>
#include <map>

#include "Logging.hpp"
#include "registry.hpp"
#include "json.hpp"

using data = nlohmann::json;

class ComponentLoader
{
private:
    static std::map<std::string, std::function<void(entt::registry&, entt::entity, const data&)>>& GetLoaders()
    {
        static std::map<std::string, std::function<void(entt::registry&, entt::entity, const data&)>> _Loaders;
        return _Loaders;
    };
    
    static void RegisterLoader(std::string typeId, std::function<void(entt::registry&, entt::entity, const data&)> loadingFunction)
    {
        GetLoaders()[typeId] = loadingFunction;
    };
    
    template <typename T>
    friend void GenerateLoadingFunction(std::string typeId, std::function<T(const data&)> loader);
    
    friend void Load(std::string typeId, entt::registry& registry, entt::entity entity, const data& data);
};

/// функция для регистрации компонента
template<class T>
void GenerateLoadingFunction(std::string typeId, std::function<T(const data&)> loader)
{
    static std::function<void(entt::registry&, entt::entity, const data&)> f =
    [loader](entt::registry& registry, entt::entity e, const data& data)
    {
        registry.emplace<T>(e, std::move(loader(data)));
    };
    
    ComponentLoader::RegisterLoader(typeId, f);
}

/// функция для загрузки компонента
void Load(std::string typeId, entt::registry& registry, entt::entity entity, const data& data)
{
    if(auto it = ComponentLoader::GetLoaders().find(typeId); it != ComponentLoader::GetLoaders().end())
    {
        it->second(registry, entity, data);
    }
       // loader(registry, entity, data);
   // assert
}




#endif /* SaveLoadComponents_hpp */
