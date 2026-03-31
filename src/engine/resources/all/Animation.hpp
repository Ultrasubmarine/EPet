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
    double _duration = 1.0;
    bool _loop = false;
    std::string _name;
    
    double _oneFrameTime = 0.0; // calculated property!
    
    Animation(const std::vector<std::shared_ptr<Texture>>& frames, double duration, bool loop, const std::string& name);
    ~Animation();
    
};
#endif /* Animation_hpp */
