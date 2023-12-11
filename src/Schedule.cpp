//
//  Schedule.cpp
//  EPet
//
//  Created by marina porkhunova on 03.12.2023.
//

#include "Schedule.hpp"
#include "RequestList.hpp"

void Schedule::Update(double dt)
{
    //poop
    _lastPoop += dt;
    if(_lastPoop > _poopDelay)
    {
        _requestList->AddRequest(RequestType::Poop);
        _lastPoop = 0;
    }
}

Schedule::Schedule(Timer *t, RequestList *r): _requestList(r)
{
    _onTimeUpdate = t->GetOnTimeUpdatedSignal().Subscribe( [this](double dt){ this->Update(dt);});
}

void Schedule::DeleteSubscription()
{
    _onTimeUpdate.lock()->Reset();
    
}
