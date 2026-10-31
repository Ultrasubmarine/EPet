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
#include <memory>
#include <string>

struct Texture;

#define DEFAULT_ANIMATION_DURATION 1.0f /// in seconds

enum class PlayMode
{
    None, // for unresolving files
    Forward,
    Reverse,
    YoYo
};

struct Animation
{
    std::vector<std::shared_ptr<Texture>> _frames;
    float _duration = DEFAULT_ANIMATION_DURATION;
    bool _loop = false;
    PlayMode _mode = PlayMode::Forward;
    
    std::string _name;
    
    float _oneFrameTime = 0.0; // calculated property!
    
    Animation(const std::vector<std::shared_ptr<Texture>>& frames, float duration, bool loop, PlayMode mode, const std::string& name);
    ~Animation();
    
};
#endif /* Animation_hpp */

