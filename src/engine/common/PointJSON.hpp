//
//  PointJSON.hpp
//  EPet
//
//  Created by marina porkhunova on 31.10.2026.
//

#ifndef PointJSON_hpp
#define PointJSON_hpp

#include "json.hpp"
#include "Point.h"

using json = nlohmann::json;

template<typename T>
void from_json(const json& j, Point<T>& p)
{
    p.x = j.at("x").get<T>();
    p.y = j.at("y").get<T>();
}

template<typename T>
void to_json(json& j, const Point<T>& p)
{
    j = json{{"x", p.x}, {"y", p.y}};
}

#endif /* PointJSON_hpp */
