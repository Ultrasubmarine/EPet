//
//  SceneManager.cpp
//  EPet
//
//  Created by marina porkhunova on 28.02.2024.
//

#include <iostream>
#include "SceneManager.hpp"

#include "Scene.hpp"
#include "Game.hpp"
#include "ResourceManager.hpp"
#include "SystemFactory.hpp"
#include "Logging.hpp"

#include "ISystem.hpp"

#include "CommonComponents.hpp"

#include "LoadComponents.hpp"
#include "SaveComponents.hpp"

using json = nlohmann::json;

/// TODO: move to utilit.cpp
std::vector<std::string> GetSystemsIds(const json* data)
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
                LOG_ERROR("LoadSystems() Empty system in json data");
            }
        }
    }
    return systemIds;
}

/// TODO: move to utilit.cpp
void LoadSystems(Scene* scene, const std::vector<std::string>& systemIds, entt::registry& registry)
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

entt::entity LoadEntity(const json* data, entt::registry& registry)
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
    
    return entity;
}


SceneManager::SceneManager(ResourceManager* r): _resourceManager(r)
{
    RegisterComponents();
  //  SystemFactory::Instance().Register("TestSystem", &TestSystem::CreateSystem);
}

/// TODO: think about another place
void SceneManager::RegisterComponents()
{
    GenerateLoadingFunction<TestComponent>("TestComponent", &TestComponent::Load);
    GenerateSaveFunction<TestComponent>("TestComponent", &TestComponent::Save);
    
    GenerateLoadingFunction<Sorting>("Sorting", &Sorting::Load);
    GenerateSaveFunction<Sorting>("Sorting", &Sorting::Save);
}

SceneManager::~SceneManager()
{
    if(_currentScene)
    {
        DeleteScene();
    }
}

void SceneManager::LoadScene(std::string id)
{
    if(!_resourceManager){
        LOG_ERROR("SceneManager::LoadScene() resourceManager didn't find. Scene Loading canceled.");
        return;
    }
    
    auto data = _resourceManager->LoadScene(id);
    if(!data) {
        LOG_ERROR("SceneManager::LoadScene() scene \""<<id<<"\" didn't find. Scene Loading canceled.");
        return;
    }
    
    if(_currentScene)
    {
        DeleteScene();
    }
    
    _currentScene = new Scene(id);
    
    //load systems
    std::vector systemIds = GetSystemsIds(data);
    LoadSystems(_currentScene, systemIds, _registry);
    
   // LoadObjects()
    // objects
    if ((*data).contains("objects"))
    {
        auto entityes = (*data)["objects"];
        for (json::iterator it = entityes.begin(); it != entityes.end(); ++it) {
            
            LoadEntity(&it.value(), _registry);
            
//            auto entity = _registry.create();
//            
//            if(!it.value().contains("components"))
//            {
//                break;
//            }
//            
//            for (auto it_comp : it.value()["components"].items())
//            {
//                if(it_comp.value().contains("id"))
//                {
//                    auto componentId = it_comp.value()["id"].get<std::string>();
//                    LoadComponent(componentId.c_str(), _registry, entity, it_comp.value());
//                }
//            }
        }
    }

    // end of loadding
    _currentScene->Start();
    OnCreate.Broadcast(_currentScene);
    delete data;
    LOG_MESSAGE("SceneManager::LoadScene() scene \""<<id<<"\" was created.");
};




void SaveEntity();


void SceneManager::SaveScene()
{
    json data;
    data["scene"] = _currentScene->GetSceneId(); // TODO: don't really need this. save as name of file
    
    // save entities with components
    for(const auto entity: _registry.view<entt::entity>())
    {
        json objectData;
        SaveAllComponentInEntity(_registry, entity, objectData);
        data["objects"].push_back(objectData);
    }
    
    //TODO: save systems
    
    LOG_MESSAGE(data);
    _resourceManager->SaveScene(_currentScene->GetSceneId(), &data);
}

void SceneManager::DeleteScene()
{
    _currentScene->Destroy();
    OnDestroy.Broadcast(_currentScene);
    delete _currentScene;
}


void SceneManager::Update(double dt)
{
    if(_currentScene)
    {
        _currentScene->Update(dt);
    }
}
