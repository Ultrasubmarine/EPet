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
    
    // end of loadding
    _currentScene->Start();
    OnCreate.Broadcast(_currentScene);
    delete data;
    LOG_MESSAGE("SceneManager::LoadScene() scene \""<<id<<"\" was created.");
};


void SceneManager::DeleteScene()
{
    _currentScene->Destroy();
    OnDestroy.Broadcast(_currentScene);
    delete _currentScene;
}
