//
//  Game.cpp
//  EPet
//
//  Created by marina porkhunova on 27.11.2023.
//

#include "Game.hpp"
#include <iostream>

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
#include "SDLWindow.h"

std::string tmpAvatar = "-----------------\n\n\n%s ^  ^\n%s(. .)          \n\n   I'm awake :)\n\n-----------------";
//bool Input();

Game::Game() //: _currentState(State::Active)
{
    //TODO: if Pet has save - load
    //...
    //Create new one
    //"[HAMSTERGOTCHI]"
    _window = new SDLWindow();
    _window->CreateWindow();
   // if(!_window)
    //    return;
    
    _timer = new Timer();
    _input = new class Input();
    
    //TODO: wrap this two to smth. it's game logic entities. but Game() manages other layer.
    _requestList = new RequestList();
    _schedule = new Schedule(_requestList);
    //TODO end
    
    //_view = new View();
    _frameRate = new FrameRate();
    _frameRate->SetFixedFrame(5);
    
    SceneManager::Instance().Init();
}

Game::~Game()
{
   // delete _view;
    delete _schedule;
    delete _requestList;
    delete _timer;
    
    Pet::Instance().Destroy();
}

void Game::Loop()
{
    _frameRate->FirstInitialization();
    
    bool isPlay = true;
    while(isPlay)
    {
        _input->Update();
        
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
    
    switch (keyCode) {
        case 'f': // food
            SceneManager::Instance().LoadScene(FEED_SCENE);
            break;
        case 'h': // happy
            Pet::Instance().IncreaseParametr(Pet::Parameter::Happy);
            break;
        case 'p': // poop
            _requestList->RemoveRequest(RequestType::Poop);
            break;
        case 's': //sick
            _requestList->RemoveRequest(RequestType::Sick);
            break;            
        default:
            break;
    }
}
