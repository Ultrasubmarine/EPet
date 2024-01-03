//
//  Schedule.cpp
//  EPet
//
//  Created by marina porkhunova on 03.12.2023.
//

#include "Schedule.hpp"
#include "RequestList.hpp"
#include "PetInfo.hpp"


bool Parameter::Update(double dt)
{
    _currentDelay -= dt;
    if(_currentDelay < 0.0001)
    {
        _callback();
        return true;
    }
    return false;
}


void Schedule::Update(double dt)
{
    _foodDecrease.Update(dt);
    _happyDecrease.Update(dt);
    _poopSpawn.Update(dt);
}

Schedule::Schedule(Timer *t, RequestList *r): _requestList(r)
{
    _onTimeUpdate = t->GetOnTimeUpdatedSignal().Subscribe( [this](double dt){ this->Update(dt);});
    
    _foodDecrease._delay = 1;
    _foodDecrease._currentDelay = _foodDecrease._delay;
    _foodDecrease._callback = [this]()
                                {   PetInfo::Instance().DecreaseParametr(Food);
                                    _foodDecrease._currentDelay = _foodDecrease._delay;
                                };
    
    _poopSpawn._delay = 10;
    _poopSpawn._currentDelay = _poopSpawn._delay;
    _poopSpawn._callback = [this]()
                                {
                                    _requestList->AddRequest(RequestType::Poop);
                                    _poopSpawn._currentDelay = _poopSpawn._delay;
                                };
    
    _happyDecrease._delay = 1;
    _happyDecrease._currentDelay = _happyDecrease._delay;
    _happyDecrease._callback = [this]()
                                {   PetInfo::Instance().DecreaseParametr(Happy);
                                    _happyDecrease._currentDelay = _happyDecrease._delay;
                                };
}

void Schedule::DeleteSubscription()
{
    _onTimeUpdate.lock()->Reset();
    
}
    
