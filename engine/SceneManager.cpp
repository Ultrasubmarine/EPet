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

#include "registry.hpp"
#include "CommonComponents.hpp"
#include <map>

std::map<std::string, std::function<void(entt::registry&, entt::entity, const json&)>>& GetLoaders()
{
    static std::map<std::string, std::function<void(entt::registry&, entt::entity, const json&)>> _Loaders;
    return _Loaders;
};

void RegisterLoader(std::string typeId, std::function<void(entt::registry&, entt::entity, const json&)> loadingFunction)
{
    GetLoaders()[typeId]=loadingFunction;
}

// общая функция для внешнего вызова
void Load(std::string typeId, entt::registry& registry, entt::entity entity, const json& data)
{
    if(auto it = GetLoaders().find(typeId); it != GetLoaders().end())
    {
        it->second(registry, entity, data);
    }
    
       // loader(registry, entity, data);
   // assert
}

template<class T>
void GenerateLoadingFunction(std::string typeId, std::function<T(const json&)> loader)
{
    static std::function<void(entt::registry&, entt::entity, const json&)> f =
    [loader](entt::registry& registry, entt::entity e, const json& data)
    {
        registry.emplace<T>(e, std::move(loader(data)));
    };
    
    RegisterLoader(typeId, f);
}

//temp place
using json = nlohmann::json;

SceneManager::SceneManager(ResourceManager* r): _resourceManager(r)
{
  //  SystemFactory::Instance().Register("TestSystem", &TestSystem::CreateSystem);
}


void Load(const json& data)
{
    auto i = (data)["value"].get<int>();
}

void SceneManager::LoadScene(std::string id)
{
    if(!_resourceManager){
        LOG_ERROR("SceneManager::LoadScene() resourceManager didn't find. Scene Loading canceled.");
        return;
    }
    
    auto data = _resourceManager->GetSceneSettings(id);
    if(!data) {
        LOG_ERROR("SceneManager::LoadScene() scene \""<<id<<"\" didn't find. Scene Loading canceled.");
        return;
    }
    
    if(_currentScene)
    {
        DeleteScene();
    }
    
    _currentScene = new Scene(id);
    
    //loadding from data
    auto systems =(*data)["systems"];
    for (json::iterator it = systems.begin(); it != systems.end(); ++it) {
        
        auto systemId = it.value().get<std::string>();

        ISystem* sys = SystemFactory::Instance().Create(systemId);
        
        if(!sys)
        {
            LOG_ERROR("SceneManager::LoadScene() System with id \""<<systemId<<"\" didn't find. system didn't added.");
        }
        _currentScene->AddSystem(systemId); // create system
    }
    
    
    // TEST CODE TO DESERIALIZE COMPONENT
    entt::registry registry;
    
    GenerateLoadingFunction<TestComponent>("TestComponent", &TestComponent::Load);
    
    auto entityes = (*data)["objects"];
    for (json::iterator it = entityes.begin(); it != entityes.end(); ++it) {
        
        auto entity = registry.create();
        
        for (auto it_comp : it.value()["components"].items())
        {
            auto componentId = it_comp.value()["id"].get<std::string>();

            Load(componentId, registry, entity, it_comp.value());
            
//           if(auto comp = registry.try_get<TestComponent>(entity))
//           {
//               bool check = true;
//           }
        }
    }
    
    // end of loadding
    _currentScene->Start();
    OnCreate.Broadcast(_currentScene);
    delete data;
    LOG_MESSAGE("SceneManager::LoadScene() scene \""<<id<<"\" was created.");
};



//template<class T>
//void Load(const json& data, entt::registry& registry, entt::entity entity)
//{
//    // то как это должно выглядеть
//    
//    std::function<T(const json&)> f ; // где и как тебя хранить?
//    registry.emplace<T>(entity, std::move(f(data)));
//    
//    
//    // 1. создать компонентик
//    if(f = compReg.GetCreateFunction(componentId); f)
//    {
//        f(registry, entity);
//    };
//    
//    bool isExist = !registry.view<TestComponent>().empty();
//    
//    // 2. заполнить компонентик даннымию
//   if(auto comp = registry.try_get<TestComponent>(entity))
//   {
//       // auto g = TestComponent::Load((*data).);
//      //  registry.emplace<TestComponent>(entity, g);
//       comp->value = it_comp.value()["value"].get<int>();
//    bool check = true;
//   }
//     
//    
//};


void CreateComponentById(entt::registry& registry, entt::entity entity, std::string& componentId)
{
    //registry.emplace<T>(entity);
};
                         
void SceneManager::DeleteScene()
{
    _currentScene->Destroy();
    OnDestroy.Broadcast(_currentScene);
    delete _currentScene;
}

