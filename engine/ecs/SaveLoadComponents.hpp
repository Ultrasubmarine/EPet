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

#define LOAD_FUNCTION_PARAMS entt::registry& registry, entt::entity entity, const data& data
using loadFunction = void(LOAD_FUNCTION_PARAMS);

class ComponentLoader
{
private:
    static std::map<std::string, std::function<loadFunction>>& GetLoaders()
    {
        static std::map<std::string, std::function<loadFunction>> _Loaders;
        return _Loaders;
    };
    
    static void RegisterLoader(std::string typeId, std::function<loadFunction> loadingFunction)
    {
        if(const auto it = GetLoaders().find(typeId); it != GetLoaders().end())
        {
            LOG_ERROR("ComponentLoader::RegisterLoader: Component loader ["<<typeId<<"] already exist. Loader registration was ignored");
            return;
        }
        GetLoaders()[typeId] = loadingFunction;
        LOG_MESSAGE("ComponentLoader::RegisterLoader: Component loader ["<<typeId<<"] registred");
    };
    
    template <typename T>
    friend void GenerateLoadingFunction(std::string typeId, std::function<T(const data&)> loader);
    
    friend void Load(std::string typeId, LOAD_FUNCTION_PARAMS);
};

/// function for component registration
template<class T>
void GenerateLoadingFunction(std::string typeId, std::function<T(const data&)> loader)
{
    static std::function<loadFunction> f =
    [loader](LOAD_FUNCTION_PARAMS)
    {
        registry.emplace<T>(entity, std::move(loader(data)));
    };
    
    ComponentLoader::RegisterLoader(typeId, f);
}

/// function for loading a component
void Load(std::string typeId, LOAD_FUNCTION_PARAMS)
{
    if(auto it = ComponentLoader::GetLoaders().find(typeId); it != ComponentLoader::GetLoaders().end())
    {
        it->second(registry, entity, data);
    }
    else
    {
        LOG_ERROR("Load: Component loader ["<<typeId<<"] didn't find. Loading component canceled");
    }
}

#endif /* SaveLoadComponents_hpp */
