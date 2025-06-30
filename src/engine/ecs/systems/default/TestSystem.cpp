//
//  TestSystem.cpp
//  EPet
//
//  Created by marina porkhunova on 19.01.2025.
//

#include "TestSystem.hpp"
#include "CommonComponents.hpp"

SYSTEM_CPP(TestSystem);

void TestSystem::Update(double dt){
    for( auto [ent, sort] : _registry.view<Sorting>().each())
    {
        int layer = sort.layer;
    }
    
    for( auto [ent, tst] : _registry.view<TestComponent>().each())
    {
        auto layer = tst.str;
    }
};


SYSTEM_CPP(AAATestSystem);

void AAATestSystem::Update(double dt){
    for( auto [ent, sort] : _registry.view<Sorting>().each())
    {
        int layer = sort.layer;
    }
    
    for( auto [ent, tst] : _registry.view<TestComponent>().each())
    {
        auto layer = tst.str;
    }
};
