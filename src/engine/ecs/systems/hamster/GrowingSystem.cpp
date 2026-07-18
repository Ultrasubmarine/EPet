//
//  GrowingSystem.cpp
//  EPet
//
//  Created by marina porkhunova on 18.07.2026.
//

#include "GrowingSystem.hpp"

#include "TimeComponents.hpp"
#include "CommonComponents.hpp"

#include "Time.hpp"
#include "Game.hpp"
#include "PlayerSave.hpp"
#include "Logging.hpp"

SYSTEM_CPP(GrowingSystem);


void GrowingSystem::Init()
{
    _playerSave = Game::Instance().GetPlayerSave();
    if(_playerSave)
    {
        // TODO think about errors. maybe optimize it. some how
        LOG_ERROR("GrowingSystem::LoadAge() saveData doesn't exist. Loading hamster level skipped");
        return;
    }
    
    int age = 0;
    std::time_t lastUpdate = 0;
    LoadAge(age, lastUpdate);

    // Recalculate timer
    // ...
    
    // Create timer
    // ...
    
    
    // WHEN Save?
//    (*saveData)["level"] = {
//        {"value", age},
//        {"lastUpdate", static_cast<std::int64_t>(std::time(nullptr))}
//    };
    
    
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

void GrowingSystem::LoadAge(int& value, std::time_t& lastUpdate)
{
    auto saveData = _playerSave->GetData();
    if(!saveData)
    {
        LOG_ERROR("GrowingSystem::LoadAge() saveData doesn't exist. Loading hamster level skipped");
        //TODO do smth for player + share logs
        return;
    }
    
    //TODO: make template for common hamster stats?
    std::string atribut_name = "age";
    
    if((*saveData).contains(atribut_name) && (*saveData)[atribut_name].is_object()) {
        const auto& levelObj = (*saveData)[atribut_name];
        if(levelObj.contains("value") && levelObj["value"].is_number_integer()) {
            value = levelObj["value"].get<int>();
        }
        if(levelObj.contains("lastUpdate") && levelObj["lastUpdate"].is_number_integer()) {
            lastUpdate = levelObj["lastUpdate"];
        }
    }
}

void GrowingSystem::Update(double dt){

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


