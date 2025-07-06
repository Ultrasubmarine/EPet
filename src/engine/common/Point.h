//
//  Point.h
//  EPet
//
//  Created by marina porkhunova on 30.06.2025.
//

#ifndef Point_h
#define Point_h


template<typename T>
struct Point {
    T x;
    T y;

    Point() = default;
    Point(T _x, T _y)
    {
        x = _x;
        y = _y;
    }
    
    Point operator+(const Point& other) const {
        return {x + other.x, y + other.y};
    }

    Point operator-(const Point& other) const {
        return {x - other.x, y - other.y};
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(x:" << p.x << " y:" << p.y << ")";
        return os;
    }
};

using IPoint = Point<int>;

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


//IPoint LoadIPoint(const json& data)
//{
//    return LoadPoint<int>(data);
//};
//void SaveIPoint(IPoint obj, json& data) { return SavePoint<int>(obj, data);};

#endif /* Point_h */
