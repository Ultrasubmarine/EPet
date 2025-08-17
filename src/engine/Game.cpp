//
//  Game.cpp
//  EPet
//
//  Created by marina porkhunova on 27.11.2023.
//

#include "Game.hpp"

#include "Logging.hpp"
#include "EngineSettings.h"

#include "FrameRate.hpp"
#include "SceneManager.hpp"
#include "ResourceManager.hpp"
#include "Input.hpp"
#include "Scene.hpp"

bool Game::Init()
{
    _window = new Window();
    if(!_window->CreateWindow())
    {
        LOG_ERROR("Game::Init() Window didn't create. Game initialization was canceled");
        return false;
    }
    
    _render = new Render();
    if(!_render->Init(_window))
    {
        LOG_ERROR("Game::Init() Render didn't create. Game initialization was canceled");
        return false;
    }

    _frameRate = new FrameRate();
    _frameRate->SetFixedFrame(5);
    
    _resourceManager = new ResourceManager();
    
    _sceneManager = new SceneManager(_resourceManager);
    _sceneManager->LoadScene("scene2"); // TODO: load abstruct scene from spechial file
    _sceneManager->SaveScene();
    return true;
}

void Game::Deinit()
{
    delete _render;
    _render = nullptr;
    
    delete _window;
    _window = nullptr;
    
    delete _frameRate;
    _frameRate = nullptr;
    
    delete _sceneManager;
    _sceneManager = nullptr;
    
    delete _resourceManager;
    _resourceManager = nullptr;
}

Game::~Game()
{
    Deinit();
}


void Game::Input()
{
    _window->HandleEvent();
    Input::Instance().Update();
    
    for(auto& key : Input::Instance().GetEvents())
    {
      //  std::cout<< key;
        if(key.State == KeyState::Pressed)
        {
            std::cout<<key.Name<<" [Pressed]\n";
            if(key.Name == "BUTTON_D"){
                Input::Instance().UnbindKey("BUTTON_A");
            }
        }
            
        if(key.State== KeyState::Released)
            std::cout<<key.Name<<" [Released]\n";
        
    }
}

void Game::RenderAll()
{
   // _render->Clear();
   // _render->Present();
}

void Game::Loop()
{
    _frameRate->FirstInitialization();
    
    bool isPlay = true;
    while(isPlay)
    {
        Input();
        _sceneManager->Update(_frameRate->GetDeltaTime());
        RenderAll();
        _frameRate->WaitFrame();
    }
}
