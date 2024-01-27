//
//  Schedule.cpp
//  EPet
//
//  Created by marina porkhunova on 03.12.2023.
//

#include "Schedule.hpp"
#include "RequestList.hpp"
#include "Pet.hpp"

Schedule::Event::Event(Type type, double delay, std::function<void()> callback, std::function<bool()> condition):
 _type(type),
 _delay(delay),
 _currentDelay(delay),
 _callback(callback),
 _condition(condition)
{
}

bool Schedule::Event::Update(double dt)
{
    _currentDelay -= dt;
    if(_currentDelay < 0.0001)
    {
        _callback();
        return true;
    }
    return false;
}

bool Schedule::Event::Condition()
{
    return _condition();
}

void Schedule::Event::Reset()
{
    _currentDelay = _delay;
}

void Schedule::Update(double dt)
{
    if(!Pet::Instance().GetIsLive())
    {
        return;
    }

    if(CheckSleep())
    {
        Pet::Instance().SetState(Pet::State::Sleep);
    }
    else
    {
        Pet::Instance().SetState(Pet::State::Usual);
        
        for(auto& e: _events)
        {
           if(e.second->Condition())
               e.second->Update(dt);
           else
               e.second->Reset();
        }
    }
}

Schedule::Schedule(RequestList *r): _requestList(r)
{
    //TODO load from file or calculate
    _currentEventsTypes = { Event::Type::HappyDecrease,
                            Event::Type::FoodDecrease,
                            Event::Type::PoopSpawn,
                            Event::Type::SickSpawn,
                            Event::Type::Death,
                            Event::Type::Birthday};
    
    for(auto& type : _currentEventsTypes)
    {
        _events.insert( {type, CreateEvent(type)});
    }
}

#include <format>
#include <ctime>

bool Schedule::CheckSleep()
{
    using namespace std::chrono;
    
    hh_mm_ss wakeUp {std::chrono::hours(9) + std::chrono::minutes(22)} ;
    hh_mm_ss goToSleep {std::chrono::hours(22) + std::chrono::minutes(16)} ;
    
    //uts - london time
    auto tp = system_clock::now();
    auto dp = floor<days>(tp);
    
    hh_mm_ss time{floor<seconds>(tp-dp)};
    auto h = time.hours();
    auto M = time.minutes();
    
    auto sleep = goToSleep.to_duration();
    auto current =time.to_duration();
    
    if(time.to_duration() > wakeUp.to_duration() && time.to_duration() < goToSleep.to_duration())
    {
        return false;
    }

    return true;
}

#include <iostream>

std::unique_ptr<Schedule::Event> Schedule::CreateEvent(Event::Type type)
{
    double delay;
    std::function<void()> callback;
    std::function<bool()> condition = [](){return true;};
          
    switch (type)
    {
        case Event::Type::FoodDecrease :
            delay = 1;
            callback = [this](){
                Pet::Instance().DecreaseParametr(Pet::Food);
                _events[Event::Type::FoodDecrease]->Reset(); };
            break;
            
        case Event::Type::HappyDecrease :
            delay = 1;
            callback = [this](){
                Pet::Instance().DecreaseParametr(Pet::Happy);
                _events[Event::Type::HappyDecrease]->Reset(); };
            break;
            
        case Event::Type::PoopSpawn :
            delay = 1;
            callback = [this](){
                _requestList->AddRequest(RequestType::Poop);
                _events[Event::Type::PoopSpawn]->Reset();  };
            condition = [this](){
                return _requestList->GetRequestsAmount(RequestType::Poop) < 3 ;};
            break;
            
        case Event::Type::SickSpawn :
            delay = 3;
            callback = [this](){
                if(_requestList->GetRequestsAmount(RequestType::Sick) < MAX_SICK)
                {
                    _requestList->AddRequest(RequestType::Sick);
                }
                _events[Event::Type::SickSpawn]->Reset(); };
            condition = [this](){
                return Pet::Instance().GetParametr(Pet::Food) == 0;};
            break;
            
        case Event::Type::Death :
            delay = 1000;
            callback = [this](){
                if(Pet::Instance().GetIsLive())
                {
                    Pet::Instance().SetState(Pet::State::Dead);
                } };
            condition = [this](){
                return _requestList->GetRequestsAmount(RequestType::Sick) == MAX_SICK && Pet::Instance().GetIsLive(); };
            break;
            
        case Event::Type::Birthday :
            delay = 5;
            callback = [this](){
                if(Pet::Instance().GetIsLive())
                {
                    Pet::Instance().IncreaseParametr(Pet::Year);
                    _events[Event::Type::Birthday]->Reset();
                } };
            break;
        default:
            std::cout<<"didn't found event to schedule"; // TODO assert
            break;
    }
    
    return std::make_unique<Event>(type, delay, callback, condition);
}
    
