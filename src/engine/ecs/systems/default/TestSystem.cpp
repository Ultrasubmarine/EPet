//
//  TestSystem.cpp
//  EPet
//
//  Created by marina porkhunova on 19.01.2025.
//

#include "TestSystem.hpp"
#include "CommonComponents.hpp"
#include "Time.hpp"

SYSTEM_CPP(TestSystem);

void TestSystem::Update(double dt){
    for( auto [ent, sort] : _registry.view<Sorting>().each())
    {
        int layer = sort.layer;
    }
    for( auto [ent, text] : _registry.view<Text>().each())
    {
        _registry.emplace_or_replace<SetNewText>(ent, Time::Instance().GetClockTimeString());
    }
    
};

