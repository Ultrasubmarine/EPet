//
//  Animation.hpp
//  EPet
//
//  Created by marina porkhunova on 08.03.2026.
//

#ifndef Animation_hpp
#define Animation_hpp

#include <stdio.h>
#include <vector>

struct Texture;

struct Animation
{
    std::vector<std::shared_ptr<Texture>> _frames;
    float _duration = 1.0f;
    bool _loop = false;
    std::string _name;
    
    Animation(const std::vector<std::shared_ptr<Texture>>& frames, float duration, bool loop, const std::string& name /* maybe name id usless property */);
};
#endif /* Animation_hpp */
