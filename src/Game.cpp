//
//  Game.cpp
//  EPet
//
//  Created by marina porkhunova on 27.11.2023.
//

#include "Game.hpp"
#include <iostream>

#include "Timer.hpp"

Game::Game() //: _currentState(State::Active)
{
    _timer = new Timer();
    SetState(State::Active);
}

Game::~Game()
{
    delete _timer;    
}

void Game::SetState(State newState)
{
    switch (newState) {
        case State::Active:
        {
            // load all active objects
            // open window
            LoadActiveObjects();
            break;
        }
        case State::Wait:
        {
            UploadActiveObjects();
            break;
        }
        default:
            break;
    }
    _currentState = newState;
}

inline void Game::LoadActiveObjects()
{
    _avatar = new PetAvatar();
}

inline void Game::UploadActiveObjects()
{
    if(_avatar)
    {
        delete _avatar;
        _avatar = nullptr;
    }
}

void Game::Loop()
{
    system("clear");
    
    if(_currentState == State::Active)
    {
        std::cout << _avatar->view;
    }
    else
    {
        std::cout << "wait state";
    }    
    _timer->PrintTime();
}
