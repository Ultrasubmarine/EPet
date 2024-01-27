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

#include "Subscription.hpp"

class RequestList;

#define MAX_SICK 2

class Schedule
{
    struct Event
    {
        enum Type
        {
            //Default
            FoodDecrease,
            HappyDecrease,
            PoopSpawn,
            SickSpawn,
            Death,
            Birthday
        };
        
        Event(double delay, std::function<void()> callback, std::function<bool()> condition = [](){return true;});
        
        Type _type;
        double _delay;
        double _currentDelay;
        std::function<void()> _callback;
        std::function<bool()> _condition;
        
        bool Update(double dt);
        bool Condition();
        void Reset();
    };
    
 //   Signal<double>::Subscription _onTimeUpdate;
    
    RequestList *_requestList;
    
    std::map<Event::Type, std::unique_ptr<Event>> _events;
    std::vector<Event::Type> _currentEventsTypes;

public:
    Schedule(RequestList *r);
  
    void Update(double dt);
    bool CheckSpeep();
    
private:
    //Factory Methods
    std::unique_ptr<Event> CreateEvent(Event::Type type);
    
};
#endif /* Schedule_hpp */
