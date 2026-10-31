//
//  AnimationLoader.cpp
//  EPet
//
//  Created by marina porkhunova on 08.03.2026.
//

#include "AnimationLoader.hpp"
#include "ResourceManager.hpp"
#include "PlayModeJSON.hpp"
#include "JsonUtils.hpp"

#include "Logger.hpp"

AnimationLoader::AnimationLoader(ResourceManager* manager): _resourceManager(manager)
{
    if(!_resourceManager)
    {
        LOG_ERROR("Resource manager is null. Animations not loaded");
    }
}

AnimationLoader::~AnimationLoader()
{
    _animations.clear();
}
    
std::shared_ptr<const Animation> AnimationLoader::GetAnimation(const std::string& name)
{
    if(auto it = _animations.find(name); it != _animations.end())
        return it->second.lock();
    
    return nullptr;
}

std::shared_ptr<const Animation> AnimationLoader::LoadAnimation(const std::string& name, const char *fullPath)
{
    if(!_resourceManager)
    {
        LOG_ERROR("Resource manager is null. Animations not loaded");
        return std::shared_ptr<const Animation>{};
    }
    
    if(auto animationData = _resourceManager->GetJson(name, ResourceType::animation))
    {
// example of json data:
//        "frames": [
//            "idle_1",
//            "idle_2",
//            "idle_3"
//        ],
//        "loop": false,
//        "duration": 2.0
        
        
        // loading from json data
        bool loop = false;
        ReadOptionalValue<bool>(*animationData, "/loop", loop);

        float duration = DEFAULT_ANIMATION_DURATION;
        ReadOptionalValue<float>(*animationData, "/duration", duration);
        if (duration <= 0.f)
        {
            LOG_WARNING("Invalid duration [" << duration << "] in [" << name << ".json]. Use default");
            duration = DEFAULT_ANIMATION_DURATION;
        }
        
        std::vector<std::string> frameNames;
        if ((*animationData).contains("frames") && (*animationData)["frames"].is_array()) {
            auto framesData =(*animationData)["frames"];
            
            for (json::iterator it = framesData.begin(); it != framesData.end(); ++it) {

                if(!it.value().is_string())
                {
                    LOG_WARNING("Incorrect frame in [" << name << ".json]. Skipped");
                    continue;
                }
                if(auto currentFrame = it.value().get<std::string>(); !currentFrame.empty())
                {
                    frameNames.push_back(std::move(currentFrame));
                }
                else{
                    LOG_WARNING("Empty frame name in [" << name << ".json]. Skipped");
                }
            }
        }
        
        PlayMode playMode = PlayMode::Forward;
        ReadOptionalValue<PlayMode>(*animationData, "/playMode", playMode);
        if( playMode == PlayMode::None)
        {
            LOG_ERROR("Unknown playMode in [" << name << ".json]. Use default");
            playMode = PlayMode::Forward;
        }
        // _____________________finish loading from json data
        
        std::vector<std::shared_ptr<Texture>> frames;
        for(auto& f : frameNames)
        {
            frames.push_back(_resourceManager->GetTexture(f));
        }
        
        
        auto resource = new Animation(frames, duration, loop, playMode, name);
        std::shared_ptr<const Animation> resource_ptr{resource};
        
        _animations[name] = std::weak_ptr<const Animation>{resource_ptr};
        return resource_ptr;
    }
    
    LOG_ERROR("Animation json [" << name << ".json] not found");
    return nullptr;
}

void AnimationLoader::ClearExpiredAnimations()
{
    for(auto it = _animations.begin(); it != _animations.end();)
    {
        if(it->second.expired())
        {
            it = _animations.erase(it);
        }
        else
        {
            it++;
        }
    }
}
