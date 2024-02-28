//
//  SceneManager.cpp
//  EPet
//
//  Created by marina porkhunova on 28.02.2024.
//

#include "SceneManager.hpp"
#include "Scene.hpp"

void SceneManager::Init()
{
    LoadScene(DEFAULT_SCENE);
}

void SceneManager::LoadScene(std::string id, std::string nextId)
{
    if(_currentScene)
    {
        DeleteScene();
    }    
    _currentScene = new Scene(id, nextId);
    OnCreate.Broadcast();
};


void SceneManager::DeleteScene()
{
    OnDestroy.Broadcast();
    delete _currentScene;
}
