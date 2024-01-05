//
//  Schedule.cpp
//  EPet
//
//  Created by marina porkhunova on 03.12.2023.
//

#include "Schedule.hpp"
#include "RequestList.hpp"
#include "PetInfo.hpp"


Event::Event(double delay, std::function<void()> callback, std::function<bool()> condition):
 _delay(delay),
 _callback(callback),
 _condition(condition)
{
    
}

bool Event::Update(double dt)
{
    _currentDelay -= dt;
    if(_currentDelay < 0.0001)
    {
        _callback();
        return true;
    }
    return false;
}

bool Event::Condition()
{
    return _condition();
}
void Event::Reset()
{
    _currentDelay = _delay;
}

void Schedule::Update(double dt)
{
    for(auto& type: _currentEventsTypes)
    {
       if(_events[type]->Condition())
       {
           _events[type]->Update(dt);
       }
       else
       {
           _events[type]->Reset();
       }
    }
}

Schedule::Schedule(Timer *t, RequestList *r): _requestList(r)
{
    _onTimeUpdate = t->GetOnTimeUpdatedSignal().Subscribe( [this](double dt){ this->Update(dt);});
    
    //TODO load from file or calculate
    _currentEventsTypes = { ScheduleEvents::FoodDecrease, ScheduleEvents::HappyDecrease, ScheduleEvents::PoopSpawn, ScheduleEvents::SickSpawn};
    for(auto& type : _currentEventsTypes)
    {
        _events[type] = CreateEvent(type);
    }
}

void Schedule::DeleteSubscription()
{
    _onTimeUpdate.lock()->Reset();
}

std::unique_ptr<Event> Schedule::CreateEvent(ScheduleEvents type)
{
    double delay;
    std::function<void()> callback;
    std::function<bool()> condition = [](){return true;};
          
    switch (type)
    {
        case ScheduleEvents::FoodDecrease :
            delay = 1;
            callback = [this](){
                PetInfo::Instance().DecreaseParametr(Food);
                _events[ScheduleEvents::FoodDecrease]->Reset(); };
            break;
        case ScheduleEvents::HappyDecrease :
            delay = 1;
            callback = [this](){
                PetInfo::Instance().DecreaseParametr(Happy);
                _events[ScheduleEvents::HappyDecrease]->Reset(); };
            break;
        case ScheduleEvents::PoopSpawn :
            delay = 1;
            callback = [this](){
                _requestList->AddRequest(RequestType::Poop);
                _events[ScheduleEvents::PoopSpawn]->Reset();  };
            break;
        case ScheduleEvents::SickSpawn :
            delay = 3;
            callback = [this](){
                if(_requestList->GetRequestsAmount(RequestType::Sick) < MAX_SICK)
                {
                    _requestList->AddRequest(RequestType::Sick);
                }
                _events[ScheduleEvents::SickSpawn]->Reset(); };
            break;
        default:
            std::cout<<"didn't found event to schedule"; // TODO assert
            break;
    }
    
    return std::make_unique<Event>(delay,callback,condition);
}
    
