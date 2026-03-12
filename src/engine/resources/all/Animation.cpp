//
//  Animation.cpp
//  EPet
//
//  Created by marina porkhunova on 08.03.2026.
//

#include "Animation.hpp"
#include "Logging.hpp"

Animation::Animation(const std::vector<std::shared_ptr<Texture>>& frames, float duration, bool loop, const std::string& name):
    _frames(frames),
    _duration(duration),
    _loop(loop),
    _name(name)
{
};

Animation::~Animation()
{
    LOG_MESSAGE("Animation::~Animation() Delete animation ["<< _name <<"]");
}


