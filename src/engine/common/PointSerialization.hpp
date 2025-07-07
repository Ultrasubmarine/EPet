//
//  PointSerialization.hpp
//  EPet
//
//  Created by marina porkhunova on 06.07.2025.
//

#ifndef PointSerialization_hpp
#define PointSerialization_hpp

#include <stdio.h>
#include "Point.h"
#include "json.hpp"

using json = nlohmann::json;

template<typename T>
Point<T> LoadPoint(const json& data)
{
    IPoint obj;
    
    obj.x= data["x"].get<T>();
    obj.y= data["y"].get<T>();
    
    return obj;
}

template<typename T>
void SavePoint(Point<T>& obj, json& data)
{
    data["x"] = obj.x;
    data["y"] = obj.y;
}

#endif /* PointSerialization_hpp */
