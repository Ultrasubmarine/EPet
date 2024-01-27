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

std::string tmpAvatar = "-----------------\n\n\n%s ^  ^\n%s(. .)          \n\n   I'm awake :)\n\n-----------------";

Game::Game() //: _currentState(State::Active)
{
    //TODO: if Pet has save - load
    //...
    //Create new one
    
    _timer = new Timer();
    _requestList = new RequestList();
    _schedule = new Schedule(_requestList);
    _view = new View();
    _frameRate = new FrameRate();
    
    _frameRate->SetFixedFrame(5);
}

Game::~Game()
{
    delete _view;
    delete _schedule;
    delete _requestList;
    delete _timer;
    
    Pet::Instance().Destroy();
}

void Game::Loop()
{
    _frameRate->FirstInitialization();
    
    while(true)
    {
        system("clear");
        
        CheckInput();
        
        _timer->Update();
        _timer->PrintTime();
        
        _schedule->Update(_frameRate->GetDeltaTime());
        _view->Update();
        _view->Draw();
        _requestList->Print();
        
        std::cout<<"\nfps: "<<1/_frameRate->GetDeltaTime()<<std::endl;
        _frameRate->WaitFrame();
    }
}

void Game::CheckInput()
{
    int keyCode = {0};
    if (StdinHasData())
    {
        keyCode = std::cin.get();
        //std::cout << "You pressed '" << keyCode << "'\n";
    }
    
    switch (keyCode) {
        case 'f': // food
            Pet::Instance().IncreaseParametr(Pet::Parameter::Food);
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
