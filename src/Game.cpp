//
//  Game.cpp
//  EPet
//
//  Created by marina porkhunova on 27.11.2023.
//

#include "Game.hpp"
#include "Logging.hpp"
#include "Timer.hpp"
#include "Schedule.hpp"
#include "RequestList.hpp"
#include "View.hpp"
#include "FrameRate.hpp"
#include "Input.hpp"

#include "Pet.hpp"
#include "SceneManager.hpp"
#include "Scene.hpp"
#include "Subscription.hpp"
#include "EngineSettings.h"

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
    
    SceneManager::Instance().Init(); //  why is it singletone? TODO: turn it to class field
    return true;
}

void Game::Deinit()
{
    delete _render;
    delete _window;
    delete _frameRate;
}

Game::~Game()
{
    Deinit();
}

void Game::Loop()
{
    _frameRate->FirstInitialization();
    
    bool isPlay = true;
    while(isPlay)
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
        
        _render->Clear();
        _render->Present();
     //   system("clear");
//        for(auto& key : _input->Get())
//        {
//            std::cout<< key.name;
//            if(key.state== KeyEvent::State::Pressed)
//                std::cout<<" [Pressed]\n";
//            if(key.state== KeyEvent::State::Released)
//                std::cout<<" [Released]\n";
//        }
       // system("clear");

        //CheckInput();
        //isPlay = Input();
        
//        _timer->Update();
//        _timer->PrintTime();
//
//        _schedule->Update(_frameRate->GetDeltaTime());
//
//        SceneManager::Instance().GetCurrentScene()->Update(_frameRate->GetDeltaTime());
//        SceneManager::Instance().GetCurrentScene()->Render(); // use scene from sceneManager Instanc because we couldn't be sure that it's the same scenes as previous
//
//        _requestList->Print();
//
//        std::cout<<"Scene: "<<SceneManager::Instance().GetCurrentScene()->GetSceneId()<<std::endl;
//        std::cout<<"\nfps: "<<1/_frameRate->GetDeltaTime()<<std::endl;
        _frameRate->WaitFrame();
        
    }
}

void Game::CheckInput()
{
    int keyCode = {0};
    //fif (StdinHasData())
    {
        keyCode = std::cin.get();
        //std::cout << "You pressed '" << keyCode << "'\n";
    }
    
    if(SceneManager::Instance().GetCurrentScene()->GetSceneId() != DEFAULT_SCENE)
    {
        return;
    }
    
//    switch (keyCode) {
//        case 'f': // food
//            SceneManager::Instance().LoadScene(FEED_SCENE);
//            break;
//        case 'h': // happy
//            Pet::Instance().IncreaseParametr(Pet::Parameter::Happy);
//            break;
//        case 'p': // poop
//            _requestList->RemoveRequest(RequestType::Poop);
//            break;
//        case 's': //sick
//            _requestList->RemoveRequest(RequestType::Sick);
//            break;            
//        default:
//            break;
//    }
}
