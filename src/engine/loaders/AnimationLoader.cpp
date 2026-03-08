//
//  AnimationLoader.cpp
//  EPet
//
//  Created by marina porkhunova on 08.03.2026.
//

#include "AnimationLoader.hpp"
#include "JsonLoader.hpp"
#include "Logging.hpp"

AnimationLoader::AnimationLoader(JsonLoader* loader): _jsonLoader(loader)
{
    if(!_jsonLoader)
    {
        LOG_ERROR("AnimationLoader::AnimationLoader() empty json loader. Impossible to load animations");
    }
}

AnimationLoader::~AnimationLoader()
{
    //TODO Delete smth?
}
    
std::shared_ptr<Animation> AnimationLoader::GetAnimation(const std::string& name)
{
    if(auto it = _animations.find(name); it != _animations.end())
        return it->second.lock() ;
    
    return nullptr;
}

std::shared_ptr<Animation> AnimationLoader::LoadAnimation(const std::string& name, const char *fullPath)
{
    if(!_jsonLoader)
    {
        LOG_ERROR("AnimationLoader::GetAnimation() empty json loader. Impossible to load animations");
        return std::shared_ptr<Animation>{};
    }
    
    if(auto animationData = _jsonLoader->GetJson(fullPath))
    {
//        "frames": [
//            "idle_1",
//            "idle_2",
//            "idle_3"
//        ],
//        "loop": false,
//        "duration": 2.0
     //   animationData["frames"];
        
        bool loop = animationData["loop"].get<bool>();
        std::vector<std::string> frames;
        
        if ((*animationData).contains("frames")) {
            auto framesData =(*animationData)["frames"];
            
            for (json::iterator it = framesData.begin(); it != framesData.end(); ++it) {

                if(auto currentFrame = it.value().get<std::string>(); !currentFrame.empty())
                {
                    frames.push_back(currentFrame);
                }
                else{
                    LOG_MESSAGE("AnimationLoader::LoadAnimation() Empty animation in animation json data");
                }
            }
        }
        
        
        std::string = animationData["imageId"].get<std::string>();
        std::shared_ptr<Animation> anim{ resource, [this](Texture* t){ this->DeleteTexture(t);}};
        
        _animations[name] = std::weak_ptr<Animation>{};
        
        delete animationData;
        return _animations[name].lock();
    }
   
    return nullptr;
}
    
void AnimationLoader::DeleteAnimation(Animation* texture)
{
    
}
