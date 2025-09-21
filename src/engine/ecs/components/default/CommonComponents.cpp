//
//  CommonComponents.cpp
//  EPet
//
//  Created by marina porkhunova on 07.07.2025.
//

#include <stdio.h>

#include "CommonComponents.hpp"
#include "Game.hpp"
#include "ResourceManager.hpp"
#include "PointSerialization.hpp"
#include "Logging.hpp"

Transform Transform::Load(const json& data)
{
    Transform obj;
    if(data.contains("position"))
    {
        obj.position = LoadPoint<int>(data["position"]);
    }
    
    return obj;
}

void Transform::Save(Transform& obj, json& data)
{
    json posData;
    SavePoint<int>(obj.position, posData);
    data["position"] = posData;
}

Sorting Sorting::Load(const json& data)
{
    Sorting obj;
    
    obj.layer= data["layer"].get<int>();
    
    return obj;
}

void Sorting::Save(Sorting& obj, json& data)
{
    data["layer"] = obj.layer;
}

Image Image::Load(const json& data)
{
    Image obj;
    if(data.contains("imageId"))
    {
        obj.resoursesId = data["imageId"].get<std::string>();
    }
    
    //TODO: Load resource callback;
    obj.resource = Game::Instance().GetResourceManager()->GetTexture(obj.resoursesId);
    return obj;
}
    
void Image::Save(Image& obj, json& data)
{
    data["imageId"] = obj.resoursesId;
}
