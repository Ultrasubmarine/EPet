//
//  Animation.hpp
//  EPet
//
//  Created by marina porkhunova on 08.03.2026.
//

#ifndef Animation_hpp
#define Animation_hpp

#include <stdio.h>
#include <list>
#include <variant>

struct Texture;

struct Animation
{
    std::list<std::shared_ptr<Texture>> _frames;
    float duration = 1.0f;
    bool loop = false;
};
#endif /* Animation_hpp */
