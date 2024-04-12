//
//  FeedingScene.cpp
//  EPet
//
//  Created by marina porkhunova on 11.03.2024.
//

#include "FeedScene.hpp"
#include "SceneManager.hpp"
#include "Pet.hpp"

#include <iostream>

FeedScene::FeedScene(std::string& id, int foodId) : Scene(id), _foodId(foodId)
{
//    std::cout<<"FeedScene: "<<_id<<" with food:"<<_foodId<<" was created";
}

FeedScene::~FeedScene()
{
//    std::cout<<"FeedScene: "<<_id<<" with food:"<<_foodId<<" was deleted";
}

void FeedScene::Start()
{
    Pet::Instance().IncreaseParametr(Pet::Parameter::Food, 4);
}

void FeedScene::Update(double dt)
{
    _animationTime -= dt;
    if(_animationTime < 0)
    {
        SceneManager::Instance().LoadScene(DEFAULT_SCENE);
    }
    
    _currentMouthTime += dt;
    if(_currentMouthTime > _mouthTime)
    {
        _currentMouthTime = 0;
        _bigMouth = !_bigMouth;
    } 
}

void FeedScene::Render()
{
    char mouth = _bigMouth == true? 'O':'o';
    printf("-----------------\n\n\n  ^  ^     /\\\n (. %c.)   () ()      \n\n   om-nom-nom \n\n-----------------\n", mouth);
    
    //Draw Tamagotchi stats
    std::cout <<"\n   PET STATS:   \n";
    std::cout <<"   Happy:" << Pet::Instance().GetParametr(Pet::Happy)<<"/"<<Pet::Instance().GetParametrMax(Pet::Happy)<<std::endl;
    std::cout <<"   Food:" << Pet::Instance().GetParametr(Pet::Food)<<"/"<<Pet::Instance().GetParametrMax(Pet::Food)<<std::endl;
    std::cout <<"   year: "<< Pet::Instance().GetParametr(Pet::Year)<<std::endl;
}

