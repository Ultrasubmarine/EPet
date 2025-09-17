//
//  Scene.cpp
//  EPet
//
//  Created by marina porkhunova on 28.02.2024.
//

#include "Scene.hpp"
#include <iostream>
#include "ISystem.hpp"
#include "Logging.hpp"

Scene::Scene(std::string& id) : _id(id)
{
    LOG_MESSAGE("Scene::Scene Scene was created. id = "  << id);
}

Scene::~Scene()
{
    for(auto s: _allSystems)
    {
        delete s;
    }
    _allSystems.clear();
}

void Scene::AddSystem(ISystem* system)
{
    _allSystems.push_back(system);
}

void Scene::AddEntity(std::string& systemId)
{
    
}

void Scene::Start()
{
    //TODO: call only overrided functions
    for(auto s: _allSystems)
    {
        s->Init();
    }
}

void Scene:: Update(double dt)
{
    //TODO: call only overrided functions
    for(auto sys: _allSystems)
    {
        sys->Update(dt);
    }
}

void Scene::Destroy()
{
    //TODO: call only overrided functions 
    for(auto s: _allSystems)
    {
        s->DeInit();
    }
    
    for(auto s: _allSystems)
    {
        delete s;
    }
}
