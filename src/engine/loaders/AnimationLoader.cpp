//
//  AnimationLoader.cpp
//  EPet
//
//  Created by marina porkhunova on 08.03.2026.
//

#include "AnimationLoader.hpp"
#include "ResourceManager.hpp"
#include "PlayModeJSON.hpp"

#include "Logging.hpp"

AnimationLoader::AnimationLoader(ResourceManager* manager): _resourceManager(manager)
{
    if(!_resourceManager)
    {
        LOG_ERROR("AnimationLoader::AnimationLoader() empty ResourceManager. Impossible to load animations");
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
        LOG_ERROR("AnimationLoader::GetAnimation() empty ResourceManager. Impossible to load animations");
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
        
        // start loading from json data
        bool loop = false;
        if ((*animationData).contains("loop") && (*animationData)["loop"].is_boolean()) {
            loop = (*animationData)["loop"].get<bool>();
        }

        float duration = 0.f;
        if ((*animationData).contains("duration") && (*animationData)["duration"].is_number()) {
            duration = (*animationData)["duration"].get<float>();
        }
        
        std::vector<std::string> frameNames;
        if ((*animationData).contains("frames") && (*animationData)["frames"].is_array()) {
            auto framesData =(*animationData)["frames"];
            
            for (json::iterator it = framesData.begin(); it != framesData.end(); ++it) {

                if(!it.value().is_string())
                {
                    LOG_MESSAGE("AnimationLoader::LoadAnimation() incorrect frame in animation json data [" << name << ".json]");
                    continue;
                }
                if(auto currentFrame = it.value().get<std::string>(); !currentFrame.empty())
                {
                    frameNames.push_back(std::move(currentFrame));
                }
                else{
                    LOG_MESSAGE("AnimationLoader::LoadAnimation() Empty animation in animation json data [" << name << ".json]");
                }
            }
        }
        
        PlayMode playMode = PlayMode::Forward;

        if (animationData->contains("playMode") && (*animationData)["playMode"].is_string()) {
            try {
                playMode = (*animationData)["playMode"].get<PlayMode>();
            } catch (const std::exception& e) {
                LOG_MESSAGE("AnimationLoader::LoadAnimation() unknown playMode in [" << name << ".json]: " << e.what());
            }
        }
        // finish loading from json data
        
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
    
    LOG_ERROR("AnimationLoader::GetAnimation() json file for animation [" << name << ".json] didn't find");
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
