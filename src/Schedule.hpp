//
//  Schedule.hpp
//  EPet
//
//  Created by marina porkhunova on 03.12.2023.
//

#ifndef Schedule_hpp
#define Schedule_hpp

#include <stdio.h>
#include <iostream>
#include <functional>

#include <vector>
#include <map>
#include <memory>

#include "Timer.hpp"
#include "Subscription.hpp"

class RequestList;

#define MAX_SICK 2

// call _callback() after current delay if _condition function return true;
struct Event
{
    Event(double delay, std::function<void()> callback, std::function<bool()> condition = [](){return true;});
    
    double _delay;
    double _currentDelay;
    std::function<void()> _callback;
    std::function<bool()> _condition;
    
    bool Update(double dt);
    bool Condition();
    void Reset();
};

enum ScheduleEvents
{
    //Default
    FoodDecrease,
    HappyDecrease,
    PoopSpawn,
    SickSpawn,
    Death    
};

class Schedule
{
    Signal<double>::Subscription _onTimeUpdate;
    Signal<int>::Subscription _onFoodChanged;
    
    RequestList *_requestList;
    
    std::map<ScheduleEvents, std::unique_ptr<Event>> _events;
    
    std::vector<ScheduleEvents> _currentEventsTypes;
    
public:
    Schedule(Timer *t, RequestList *r);
  
    bool CheckSpeep();
    void Update(double dt);
    void DeleteSubscription();
    
private:
    //Factory Methods
    std::unique_ptr<Event> CreateEvent(ScheduleEvents type);
    
};
#endif /* Schedule_hpp */
