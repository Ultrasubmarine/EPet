//
//  LambdaScene.cpp
//  EPet
//
//  Created by marina porkhunova on 12.04.2024.
//

#include "LambdaScene.hpp"
#include <iostream>

LambdaScene::LambdaScene(std::string& id, std::function<void()> startCallback, std::function<void(double)> updateCallback, std::function<void()> destroyCallback) : Scene(id),
                    _onStart(startCallback),
                    _onUpdate(updateCallback),
                    _onDestroy(destroyCallback)
{
 //   std::cout<<"LambdaScene: "<<_id<<" was created";
}

LambdaScene::~LambdaScene()
{
 //   std::cout<<"LambdaScene: "<<_id<<" was deleted";
    if(_onDestroy)
    {
        _onDestroy();
    }
}

void LambdaScene::Start()
{
    if(_onStart)
    {
        _onStart();
    }
}

void LambdaScene::Update(double dt)
{
    if(_onUpdate)
    {
        _onUpdate(dt);
    }
};

void LambdaScene::Render()
{
    std::cout<<"Lambda render: "<<i;
}
