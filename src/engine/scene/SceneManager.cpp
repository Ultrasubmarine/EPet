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
#include "Game.hpp"
#include "Scene.hpp"

using json = nlohmann::json;

SceneManager::SceneManager()
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
    auto resourceManager = Game::Instance().GetResourceManager();
    if(!resourceManager){
        LOG_ERROR("Resource manager is null. Scene loading canceled");
        return;
    }
    
    auto data = resourceManager->GetJson(id, ResourceType::scene);
    if(!data) {
        LOG_ERROR("Scene [" << id << "] not found. Scene loading canceled");
        return;
    }
    
    if(_currentScene)
    {
        DeleteScene();
    }
    
    _currentScene = new Scene(id);
    
    std::vector systemIds = GetSystemsIds(data.get());
    LoadSystems(_currentScene, systemIds, _registry);
    LoadObjects(data.get(), _registry);

    // end of loadding
    _currentScene->Start();
    OnCreate.Broadcast(_currentScene);
    
    LOG_MESSAGE("Scene [" << id << "] loaded");
};

void SceneManager::SaveScene()
{
    json data; // TODO: maybe if it's too big it's better to convert it to pointer* with new.
    data["scene"] = _currentScene->GetSceneId(); // TODO: don't really need this. save as name of file
    
    SaveSystems(data, _currentScene);
    SaveObjects(data, _registry);
    
    std::string dataScene = data.dump(1, '\t');
   // LOG_MESSAGE(dataScene);
    
    auto resourceManager = Game::Instance().GetResourceManager();
    if(!resourceManager){
        LOG_ERROR("Resource manager is null. Scene saving canceled");
        return;
    }
    resourceManager->SaveJson(_currentScene->GetSceneId() + "1", &data, ResourceType::scene);
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
