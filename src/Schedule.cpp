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
_currentDelay(delay),
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
    for(auto& e: _events)
    {
       if(e.second->Condition())
           e.second->Update(dt);
       else
           e.second->Reset();
    }
}

Schedule::Schedule(Timer *t, RequestList *r): _requestList(r)
{
    _onTimeUpdate = t->GetOnTimeUpdatedSignal().Subscribe( [this](double dt){ this->Update(dt);});
    
    //TODO load from file or calculate
    _currentEventsTypes = { ScheduleEvents::HappyDecrease, ScheduleEvents::FoodDecrease, ScheduleEvents::PoopSpawn, ScheduleEvents::SickSpawn, ScheduleEvents::Death};
    
    for(auto& type : _currentEventsTypes)
    {
        _events.insert( {type, CreateEvent(type)});
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
            condition = [this](){
                return _requestList->GetRequestsAmount(RequestType::Poop) < 3 ;};
            break;
            
        case ScheduleEvents::SickSpawn :
            delay = 3;
            callback = [this](){
                if(_requestList->GetRequestsAmount(RequestType::Sick) < MAX_SICK)
                {
                    _requestList->AddRequest(RequestType::Sick);
                }
                _events[ScheduleEvents::SickSpawn]->Reset(); };
            condition = [this](){
                return PetInfo::Instance().GetParametr(Food) == 0;};
            break;
            
        case ScheduleEvents::Death :
            delay = 3;
            callback = [this](){
                if(PetInfo::Instance().GetIsLive())
                {
                    PetInfo::Instance().SetIsLive(false);
                } };
            condition = [this](){
                return _requestList->GetRequestsAmount(RequestType::Sick) == MAX_SICK && PetInfo::Instance().GetIsLive(); };
            break;
            
        default:
            std::cout<<"didn't found event to schedule"; // TODO assert
            break;
    }
    
    return std::make_unique<Event>(delay,callback,condition);
}
    
