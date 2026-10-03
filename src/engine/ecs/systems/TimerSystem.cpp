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
//    entt::entity entity;
//    if(CreateTimer(10.0, &entity))
//    {
//        _registry.emplace<Text>(entity);
//        _registry.emplace<SetNewFont>(entity, DEFAULT_FONT);
//        
//        _registry.emplace<RendererObject>(entity);
//        _registry.emplace<Sorting>(entity, 1000);
//        _registry.emplace<Transform>(entity, IPoint(50, 50));
//    }
}

void TimerSystem::Update(double dt){

    // Delete all one frame components
    _registry.clear<TimerFinished_OF>();
    
    // Delete timer that not use anymore
    for(auto entity : _registry.view<UnusedTimer>()) {
        _registry.destroy(entity);
    }
    
    // Update timers
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
    
    // Show timers
    for( auto [ent, timer, text] : _registry.view<Timer, Text>().each())
    {
        int totalSeconds = static_cast<int>(std::round(std::max(0.0, timer.timeLeft)));
        int minutes = totalSeconds / 60;
        int seconds = totalSeconds % 60;

        char buf[6];
        std::snprintf(buf, sizeof(buf), "%2d:%02d", minutes, seconds);

        _registry.emplace_or_replace<SetNewText>(ent, buf);
    }
};

