//
//  Schedule.cpp
//  EPet
//
//  Created by marina porkhunova on 03.12.2023.
//

#include "Schedule.hpp"

Schedule::Schedule(Timer *t)
{
  //  auto callback =[this](){ this->CalculatePoop();};
    _onTimeUpdate = t->GetOnTimeUpdatedSignal().Subscribe( [this](){ this->CalculatePoop();});
}
