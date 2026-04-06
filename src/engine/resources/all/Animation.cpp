//
//  Animation.cpp
//  EPet
//
//  Created by marina porkhunova on 08.03.2026.
//

#include "Animation.hpp"
#include "Logging.hpp"

Animation::Animation(const std::vector<std::shared_ptr<Texture>>& frames, float duration, bool loop, PlayMode mode, const std::string& name):
    _frames(frames),
    _duration(duration),
    _loop(loop),
    _mode(mode),
    _name(name)
{
    if(mode != PlayMode::YoYo)
        _oneFrameTime = _duration / _frames.size();
    else
        _oneFrameTime = _duration / (_frames.size() * 2);
};

Animation::~Animation()
{
    LOG_MESSAGE("Animation::~Animation() Delete animation ["<< _name <<"]");
}


