//
//  Game.cpp
//  EPet
//
//  Created by marina porkhunova on 27.11.2023.
//

#include "Game.hpp"

#include "Logger.hpp"
#include "EngineSettings.h"

#include "GameSettings.hpp"
#include "FrameRate.hpp"
#include "SceneManager.hpp"
#include "ResourceManager.hpp"
#include "Input.hpp"
#include "PlayerSave.hpp"
#include "Time.hpp"

Game::Game() = default;

bool Game::Init()
{
    _resourceManager = std::make_unique<ResourceManager>();
    
    // load game settings
    auto file = _resourceManager->GetJson(_gameSettingsFileName, ResourceType::settings);
    _settings = std::make_unique<GameSettings>(file);
    delete file; // TODO: move to smart pointers for json

    _window = std::make_unique<Window>();
    if(!_window->CreateWindow(_settings->GetWidth(), _settings->GetHeight(), _settings->GetTitle().c_str()))
    {
        LOG_ERROR("Window didn't create. Game initialization was canceled");
        return false;
    }
    
    _render = std::make_unique<Render>();
    if(!_render->Init(_window.get()))
    {
        LOG_ERROR("Render didn't create. Game initialization was canceled");
        return false;
    }
    
    Time::Instance().Init(); // before scenes!

    _frameRate = std::make_unique<FrameRate>();
    _frameRate->SetFixedFrame(_settings->GetFps());
    
    _playerSave = std::make_unique<PlayerSave>();
    if(!_playerSave->Load()) {
        _playerSave->Save();
    }
    
    _sceneManager = std::make_unique<SceneManager>();
    return true;
}

void Game::Start()
{
    _sceneManager->LoadScene(_settings->GetStartScene());
}

void Game::Deinit()
{
    _sceneManager.reset();
    _playerSave.reset();
    _frameRate.reset();
    _settings.reset();
    _resourceManager.reset();
    
    _render.reset();
    _window.reset();
}

Game::~Game()
{
    Deinit();
}

void Game::HandleInput()
{
    //TODO: handle some events
    
    _window->HandleEvent();
    Input::Instance().Update();

//    for(auto& key : Input::Instance().GetEvents())
//    {
//      //  std::cout<< key;
//        if(key.State == KeyState::Pressed)
//        {
//            std::cout<<key.Name<<" [Pressed]\n";
//            if(key.Name == "BUTTON_D"){
//                Input::Instance().UnbindKey("BUTTON_A");
//            }
//        }
//            
//        if(key.State== KeyState::Released)
//            std::cout<<key.Name<<" [Released]\n";
//        
//    }
}

void Game::Loop()
{
    _frameRate->FirstInitialization();
    
    while(!_window->IsCloseRequested())
    {
        HandleInput();
        double dt = _frameRate->GetDeltaTime(); // in seconds

        Time::Instance().Update(dt);
        _sceneManager->Update(dt);

        _frameRate->WaitFrame();
    }
}

