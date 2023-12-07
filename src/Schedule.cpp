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
   // _g.Reset();
    _onTimeUpdate = t->GetOnTimeUpdatedSignal().Subscribe( [this](int a){ this->CalculatePoop();});
    
    _g = t->GetOnTimeUpdatedSignalWithoutParametrs().Subscribe([this](){std::cout<<"omg. work\n";});//this->DeleteSubscription();
    _onTimeUpdate.lock()->Reset();
  
}

void Schedule::DeleteSubscription()
{
    _onTimeUpdate.lock()->Reset();
    
}
