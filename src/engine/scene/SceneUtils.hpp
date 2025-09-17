//
//  SceneUtils.hpp
//  EPet
//
//  Created by marina porkhunova on 28.06.2025.
//

#ifndef SceneUtils_hpp
#define SceneUtils_hpp

#include <stdio.h>
#include <string>
#include <vector>

#include "Logging.hpp"
#include "Scene.hpp"

#include "SystemFactory.hpp"

#include "LoadComponents.hpp"
#include "SaveComponents.hpp"

#include "registry.hpp"
#include "json.hpp"

using json = nlohmann::json;
class Scene;

//____________________________________
// LOADING SCENE HELPING FUNCTIONS:
inline std::vector<std::string> GetSystemsIds(const json* data)
{
    std::vector<std::string> systemIds{};
    if ((*data).contains("systems")) {
        auto systems =(*data)["systems"];
        for (json::iterator it = systems.begin(); it != systems.end(); ++it) {

            if(auto systemId = it.value().get<std::string>(); !systemId.empty())
            {
                systemIds.push_back(systemId);
            }
            else{
                LOG_MESSAGE("LoadSystems() Empty system in json data");
            }
        }
    }
    return systemIds;
}

inline void LoadSystems(Scene* scene, const std::vector<std::string>& systemIds, entt::registry& registry)
{
    for(const auto& systemId: systemIds)
    {
        ISystem* sys = SystemFactory::Instance().Create(systemId, registry);
        if(!sys)
        {
            LOG_ERROR("LoadSystems() System with id \""<<systemId<<"\" didn't find in SystemFactory. system didn't added.");
        }
        scene->AddSystem(sys); // create system
    }
}

inline entt::entity LoadObject(const json* data, entt::registry& registry)
{
    auto entity = registry.create();
    
    if((*data).contains("components"))
    {
        for (auto it_comp : (*data)["components"].items())
        {
            if(it_comp.value().contains("id"))
            {
                auto componentId = it_comp.value()["id"].get<std::string>();
                LoadComponent(componentId.c_str(), registry, entity, it_comp.value());
            }
        }
    }
    // TODO: if child
    // TODO: if prefab
    
    return entity;
}

inline void LoadObjects(const json* data, entt::registry& registry)
{
    if ((*data).contains("objects"))
    {
        auto entityes = (*data)["objects"];
        for (json::iterator it = entityes.begin(); it != entityes.end(); ++it) {
            
            LoadObject(&it.value(), registry);
        }
    }
}

// LOADING SCENE HELPING FUNCTIONS END
//____________________________________

// SAVING SCENE HELPING FUNCTIONS:
inline void SaveSystems(json& data, const Scene* scene)
{
    for(const auto& sys: scene->GetSystems())
    {
        auto id = sys->GetSystemId();
        data["systems"].push_back(id);
    }
}

// TODO: change registry on different structure that takes sorted entityes !!!
inline void SaveObjects(json& data, entt::registry& registry)
{
    for(const auto entity: registry.view<entt::entity>())
    {
        json objectData;
        SaveAllComponentInEntity(registry, entity, objectData);
        data["objects"].push_back(objectData);
    }
}
// SAVING SCENE HELPING FUNCTIONS END

#endif /* SceneUtils_hpp */
