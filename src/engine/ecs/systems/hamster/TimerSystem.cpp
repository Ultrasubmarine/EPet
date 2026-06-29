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
    entt::entity entity;
    if(CreateTimer(10.0, &entity))
    {
        _registry.emplace<Text>(entity);
        _registry.emplace<SetNewFont>(entity, DEFAULT_FONT);
        
        _registry.emplace<RendererObject>(entity);
        _registry.emplace<Sorting>(entity, 1000);
        _registry.emplace<Transform>(entity, IPoint(50, 50));
    }
}

void TimerSystem::Update(double dt){
    
    dt = dt/1000.0; // dt in miliseconds but here we need seconds;
    
    // delete all one frame components
    _registry.clear<TimerFinished_OF>();
    
    
    //update timers
    for( auto [ent, timer] : _registry.view<Timer>(entt::exclude<TimerFinished>).each())
    {
        timer.timeLeft -= dt;
        
        // if completed
        if(timer.timeLeft <= 0.0)
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

