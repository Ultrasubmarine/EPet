//
//  TestSystem.cpp
//  EPet
//
//  Created by marina porkhunova on 19.01.2025.
//

#include "TimerSystem.hpp"

#include "TimeComponents.hpp"
#include "CommonComponents.hpp"

#include "Time.hpp"

SYSTEM_CPP(TimerSystem);


void TimerSystem::Init()
{
    entt::entity* ent_ptr;
    if(CreateTimer(10.0, ent_ptr))
    {
        _registry.emplace<Text>(*ent_ptr);
        _registry.emplace<SetNewFont>(*ent_ptr, DEFAULT_FONT);
        
        _registry.emplace<Sorting>(*ent_ptr, 1000);
        _registry.emplace<Transform>(*ent_ptr, IPoint(50, 50));
    }
}

void TimerSystem::Update(double dt){
    
    // delete all one frame components
    _registry.clear<TimerFinished_OF>();
    
    
    //update timers
    for( auto [ent, timer] : _registry.view<Timer>(entt::exclude<TimerFinished>).each())
    {
        timer.timeLeft -= dt;
        
        // if completed
        if(timer.timeLeft <= -0.001)
        {
            _registry.emplace<TimerFinished_OF>(ent);
            _registry.emplace<TimerFinished>(ent);
        }
    }
    
    //show timers
    for( auto [ent, timer, text] : _registry.view<Timer, Text>().each())
    {
        _registry.emplace_or_replace<SetNewText>(ent, std::to_string(timer.timeLeft));
    }
};

