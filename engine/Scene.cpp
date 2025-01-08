//
//  Scene.cpp
//  EPet
//
//  Created by marina porkhunova on 28.02.2024.
//

#include "Scene.hpp"
#include <iostream>


void Scene::AddSystem(std::string& systemId)
{
    
}

void Scene::AddEntity(std::string& systemId)
{
    
}

Scene::Scene(std::string& id) : _id(id)
{
 //   std::cout<<"Scene: "<<_id<<" was created";
}

Scene::~Scene()
{
//    std::cout<<"Scene: "<<_id<<" was deleted";
}
