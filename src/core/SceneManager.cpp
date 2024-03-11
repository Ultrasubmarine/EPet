//
//  SceneManager.cpp
//  EPet
//
//  Created by marina porkhunova on 28.02.2024.
//

#include "SceneManager.hpp"
#include <iostream>

#include "Scene.hpp"
#include "MainScene.hpp"
#include "FeedScene.hpp"

void SceneManager::Init()
{
    LoadScene(DEFAULT_SCENE);
}

void SceneManager::LoadScene(std::string id)
{
    if(_currentScene)
    {
        DeleteScene();
    }
    
    if(id == DEFAULT_SCENE)
    {
        _currentScene = new MainScene(id);
    }
    else if(id == FEED_SCENE)
    {
        _currentScene = new FeedScene(id,1);
    }
    else
    {
        std::cout<<"we dont know this scene";
        _currentScene = new Scene(id);
    }
   
    _currentScene->Start();
    OnCreate.Broadcast(_currentScene);
};


void SceneManager::DeleteScene()
{
    OnDestroy.Broadcast(_currentScene);
    delete _currentScene;
}
