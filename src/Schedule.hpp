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

class Schedule
{
    Signal<int>::Subscription _onTimeUpdate;
    Signal<>::Subscription _g;
    Signal<>::Subscription _gg;
    // _f;
    
 //   Signal<void>::_Subscription g;
   // Signal<void>::SubscriptionPtr
   // Signal<void>::Subscription
public:
    Schedule(Timer* t);
    void CalculatePoop()
    {
        std::cout<<"poop";
    };
    
    void DeleteSubscription();
};
#endif /* Schedule_hpp */
