//
//  AnimationLoader.cpp
//  EPet
//
//  Created by marina porkhunova on 08.03.2026.
//

#include "AnimationLoader.hpp"
#include "JsonLoader.hpp"
#include "Logging.hpp"
#include "Game.hpp"
#include "ResourceManager.hpp"

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
// #example of json data:
//        "frames": [
//            "idle_1",
//            "idle_2",
//            "idle_3"
//        ],
//        "loop": false,
//        "duration": 2.0
        
        bool loop = (*animationData)["loop"].get<bool>();
        float duration = (*animationData)["duration"].get<float>();
        
        std::vector<std::string> frameNames;
        
        if ((*animationData).contains("frames")) {
            auto framesData =(*animationData)["frames"];
            
            for (json::iterator it = framesData.begin(); it != framesData.end(); ++it) {

                if(auto currentFrame = it.value().get<std::string>(); !currentFrame.empty())
                {
                    frameNames.push_back(currentFrame);
                }
                else{
                    LOG_MESSAGE("AnimationLoader::LoadAnimation() Empty animation in animation json data");
                }
            }
        }
        delete animationData;
        // finish loading from data
        
        
        std::vector<std::shared_ptr<Texture>> frames;
        if (auto resources = Game::Instance().GetResourceManager())
        {
            for(auto& f : frameNames)
            {
                frames.push_back(resources->GetTexture(f));
            }
        }
      
        auto resource = new Animation(frames, duration, loop, name);
        std::shared_ptr<Animation> resource_ptr{ resource, [this](Animation* obj){ this->DeleteAnimation(obj);}};
        
        _animations[name] = std::weak_ptr<Animation>{resource_ptr};
        return resource_ptr;
    }
   
    return nullptr;
}
    
void AnimationLoader::DeleteAnimation(Animation* res)
{
    LOG_MESSAGE("AnimationLoader::DeleteAnimation() Animation ["<< res->_name <<"]");
    _animations.erase(res->_name);
    
    delete res;
}
