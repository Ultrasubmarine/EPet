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

#include "Timer.hpp"
#include "Subscription.hpp"

class RequestList;

class Schedule
{
    Signal<double>::Subscription _onTimeUpdate;

    RequestList *_requestList;
    
    double _lastPoop;
    const double _poopDelay = 15.0;
    
public:
    Schedule(Timer *t, RequestList *r);
  
    void Update(double dt);
    void DeleteSubscription();
};
#endif /* Schedule_hpp */
