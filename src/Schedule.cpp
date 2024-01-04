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

void Parameter::Reset()
{
    _currentDelay = _delay;
}

void Schedule::Update(double dt)
{
    _foodDecrease.Update(dt);
    _happyDecrease.Update(dt);
    _poopSpawn.Update(dt);
    
    if(PetInfo::Instance().GetParametr(Food) == 0)
    {
        _sickSpawn.Update(dt);
    }
    else
    {
        _sickSpawn.Reset();
    }
}

Schedule::Schedule(Timer *t, RequestList *r): _requestList(r)
{
    _onTimeUpdate = t->GetOnTimeUpdatedSignal().Subscribe( [this](double dt){ this->Update(dt);});
    
    _foodDecrease._delay = 1;
    _foodDecrease._currentDelay = _foodDecrease._delay;
    _foodDecrease._callback = [this]()
                                {   PetInfo::Instance().DecreaseParametr(Food);
                                    _foodDecrease.Reset();
                                };
    
    _poopSpawn._delay = 2;
    _poopSpawn._currentDelay = _poopSpawn._delay;
    _poopSpawn._callback = [this]()
                                {
                                    _requestList->AddRequest(RequestType::Poop);
                                    _poopSpawn.Reset();
                                };
    
    _happyDecrease._delay = 1;
    _happyDecrease._currentDelay = _happyDecrease._delay;
    _happyDecrease._callback = [this]()
                                {
                                    PetInfo::Instance().DecreaseParametr(Happy);
                                    _happyDecrease.Reset();
                                };
    
    _sickSpawn._delay = 3;
    _sickSpawn._currentDelay = _sickSpawn._delay;
    _sickSpawn._callback = [this]()
                            {
                                if(_requestList->GetRequestsAmount(RequestType::Sick) < 2)
                                {
                                    _requestList->AddRequest(RequestType::Sick);
                                }
                                _sickSpawn._currentDelay = _sickSpawn._delay;
                            };
    
    _onFoodChanged = PetInfo::Instance().GetParameterSignal(Food)->Subscribe(
                                                [this](int foodValue)
                                                {
                                                    if(foodValue > 0)
                                                        _sickSpawn.Reset();
                                                });
}

void Schedule::DeleteSubscription()
{
    _onTimeUpdate.lock()->Reset();
    
}
    
