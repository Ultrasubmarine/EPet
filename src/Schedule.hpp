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
    Subscription* _onTimeUpdate;
    
public:
    Schedule(Timer* t);
    void CalculatePoop()
    {
        std::cout<<"poop";
    };
};
#endif /* Schedule_hpp */
