//
//  SceneManager.cpp
//  EPet
//
//  Created by marina porkhunova on 28.02.2024.
//

#include <iostream>
#include <memory>

#include "SceneManager.hpp"

#include "RegisterComponents.hpp"
#include "ResourceManager.hpp"
#include "SceneUtils.hpp"
#include "Scene.hpp"

using json = nlohmann::json;

SceneManager::SceneManager(ResourceManager* r): _resourceManager(r)
{
    RegisterComponents();
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
    
    auto data_ptr = _resourceManager->LoadScene(id);
    if(!data_ptr) {
        LOG_ERROR("SceneManager::LoadScene() scene \""<<id<<"\" didn't find. Scene Loading canceled.");
        return;
    }
    const auto data = data_ptr.get();
    
    if(_currentScene)
    {
        DeleteScene();
    }
    
    _currentScene = new Scene(id);
    
    //load systems
    std::vector systemIds = GetSystemsIds(data);
    LoadSystems(_currentScene, systemIds, _registry);
    
   //load objects
    LoadObjects(data, _registry);

    // end of loadding
    _currentScene->Start();
    OnCreate.Broadcast(_currentScene);
    
   // delete data;
    LOG_MESSAGE("SceneManager::LoadScene() scene \""<<id<<"\" was created.");
};

void SceneManager::SaveScene()
{
    json data; // TODO: maybe if it's too big it's better to convert it to pointer* with new. 
    data["scene"] = _currentScene->GetSceneId(); // TODO: don't really need this. save as name of file
    
    SaveSystems(data, _currentScene);
    SaveObjects(data, _registry);
    
    std::string dataScene = data.dump(1, '\t');
    LOG_MESSAGE(dataScene);
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
