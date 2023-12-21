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

#include "Timer.hpp"
#include "Subscription.hpp"

class RequestList;


struct Parameter
{
    double _delay;
    double _currentDelay;
    std::function<void()> _callback;
    
    bool Update(double dt);
};

class Schedule
{
    Signal<double>::Subscription _onTimeUpdate;

    RequestList *_requestList;
    
    Parameter _foodDecrease;
    Parameter _happyDecrease;
    Parameter _poopSpawn;
    
public:
    Schedule(Timer *t, RequestList *r);
  
    void Update(double dt);
    void DeleteSubscription();
};
#endif /* Schedule_hpp */
