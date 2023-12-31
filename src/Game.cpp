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

#include "PetInfo.hpp"

std::string tmpAvatar = "-----------------\n\n\n%s ^  ^\n%s(. .)          \n\n   I'm awake :)\n\n-----------------";

Game::Game() //: _currentState(State::Active)
{
    //TODO: if PetInfo has save - load
    //...
    //Create new one
    PetInfo::Instance().SetAvatar(tmpAvatar);
    
    _timer = new Timer();
    _requestList = new RequestList();
    _schedule = new Schedule(_timer, _requestList);
    _view = new View(_requestList);
    _frameRate = new FrameRate();
    
    _frameRate->SetFixedFrame(5);
}

Game::~Game()
{
    delete _view;
    delete _schedule;
    delete _requestList;
    delete _timer;
    
    PetInfo::Instance().Destroy();
}

void Game::Loop()
{
    _frameRate->FirstInitialization();
    
    while(true)
    {
        system("clear");
        _timer->Update();
        _timer->PrintTime();
        
        _requestList->Print();
        _view->Update();
        _view->Draw();
        
        std::cout<<"\nfps: "<<1/_frameRate->GetDeltaTime()<<std::endl;
        _frameRate->WaitFrame();
    }
}
