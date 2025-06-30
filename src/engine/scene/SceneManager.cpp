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

#include "SceneUtils.hpp"

using json = nlohmann::json;

SceneManager::SceneManager(ResourceManager* r): _resourceManager(r)
{
    RegisterComponents();
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
    
   //load objects
    LoadObjects(data, _registry);

    // end of loadding
    _currentScene->Start();
    OnCreate.Broadcast(_currentScene);
    
    delete data;
    LOG_MESSAGE("SceneManager::LoadScene() scene \""<<id<<"\" was created.");
};

void SceneManager::SaveScene()
{
    json data;
    data["scene"] = _currentScene->GetSceneId(); // TODO: don't really need this. save as name of file
    
    SaveSystems(data, _currentScene);
    SaveObjects(data, _registry);
    
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
