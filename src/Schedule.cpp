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
    
    _g = t->GetOnTimeUpdatedSignalWithoutParametrs().Subscribe([this](){std::cout<<"q connect\n";
        this->_g.lock()->Reset();
    });
    _gg = t->GetOnTimeUpdatedSignalWithoutParametrs().Subscribe([this](){std::cout<<"qq connect\n";
    });
    
    _onTimeUpdate.lock()->Reset();
  
}

void Schedule::DeleteSubscription()
{
    _onTimeUpdate.lock()->Reset();
    
}
