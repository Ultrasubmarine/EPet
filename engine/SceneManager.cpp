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
#include "SaveLoadComponents.hpp"
#include <map>

//temp place
//using json = nlohmann::json;

SceneManager::SceneManager(ResourceManager* r): _resourceManager(r)
{
  //  SystemFactory::Instance().Register("TestSystem", &TestSystem::CreateSystem);
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
    GenerateLoadingFunction<TestComponent>("TestComponent", &TestComponent::Load);
    
    auto entityes = (*data)["objects"];
    for (json::iterator it = entityes.begin(); it != entityes.end(); ++it) {
        
        auto entity = _registry.create();
        
        for (auto it_comp : it.value()["components"].items())
        {
            auto componentId = it_comp.value()["id"].get<std::string>();

            Load(componentId.c_str(), _registry, entity, it_comp.value());
            
           if(auto comp = _registry.try_get<TestComponent>(entity))
           {
               bool check = true;
           }
        }
    }
    // end of loadding
    _currentScene->Start();
    OnCreate.Broadcast(_currentScene);
    delete data;
    LOG_MESSAGE("SceneManager::LoadScene() scene \""<<id<<"\" was created.");
};


#define SAVE_FUNCTION_PARAMS entt::registry& registry, entt::entity entity, data& data
using saveFunction = void(entt::registry& registry, entt::entity entity, json& data);


class ComponentSaver
{
private:
    static std::map<std::string, std::function<saveFunction>>& GetSavers()
    {
        static std::map<std::string, std::function<saveFunction>> _Savers;
        return _Savers;
    };
    
    static void RegisterSaver(std::string typeId, std::function<saveFunction> saveFunction)
    {
        if(const auto it = GetSavers().find(typeId); it != GetSavers().end())
        {
            LOG_ERROR("ComponentSaver::RegisterSaver: Component saver ["<<typeId<<"] already exist. Saver registration was ignored");
            return;
        }
        GetSavers()[typeId] = saveFunction;
        LOG_MESSAGE("ComponentSaver::RegisterSaver: Component saver ["<<typeId<<"] registred");
    };
    
    template <typename T>
    friend void GenerateSaveFunction(const char* typeId, std::function<void(entt::registry&, entt::entity, data&)> saver);
    
    friend void Save(const char* typeId, SAVE_FUNCTION_PARAMS);
    friend void SaveAllComponentInEntity(entt::registry& registry, entt::entity entity);
};


/// function for component registration
template<class T>
void GenerateSaveFunction(const char* typeId, std::function<void(entt::registry& registry, entt::entity, data&)> saver)
{
    static std::function<void(entt::registry&, entt::entity, data&)> f =
    [saver](entt::registry& registry, entt::entity entity, data& data)
    {
        if(const auto comp = registry.try_get<T>(entity))
        {
            saver(comp, data);
        }
    };
    
    ComponentSaver::RegisterSaver(typeId, f);
}

/// function for saving a component
void Save(const char* typeId, SAVE_FUNCTION_PARAMS)
{
    if(auto it = ComponentSaver::GetSavers().find(typeId); it != ComponentSaver::GetSavers().end())
    {
        it->second(registry, entity, data);
    }
    else
    {
        LOG_ERROR("Load: Component saver ["<<typeId<<"] didn't find. Saving component canceled");
    }
}

void SaveAllComponentInEntity(entt::registry& registry, entt::entity entity)
{
    
}


void SceneManager::SaveScene()
{
    
//    std::vector<entt::entity> savePool;
//    json data;
//    
//    for(const auto e: savePool)
//    {
//    // пройтись по всем компонентам с ID и сохранить
//     for(id: saveId)
//       if(const comp = _registry.try_get<T>(e))
//       {
//           Save(T, comp, data);
//       }
//    }
    
}

//template <class T>
//std::string GetTypeId()
//{
//    return str;
//}
//  
//
//template <class T>
//void RegisterSave(std::string& typeId, )



void SceneManager::DeleteScene()
{
    _currentScene->Destroy();
    OnDestroy.Broadcast(_currentScene);
    delete _currentScene;
}

