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
    
    Point operator+(const Point& other) {
        return {x + other.x, y + other.y};
    }

    Point operator-(const Point& other) {
        return {x - other.x, y - other.y};
    }
    
    Point& operator+=(const Point& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    
    Point& operator-=(const Point& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(x:" << p.x << " y:" << p.y << ")";
        return os;
    }
};

using IPoint = Point<int>;

#endif /* Point_h */
