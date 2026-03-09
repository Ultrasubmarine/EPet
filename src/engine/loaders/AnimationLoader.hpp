//
//  AnimationLoader.hpp
//  EPet
//
//  Created by marina porkhunova on 08.03.2026.
//

#ifndef AnimationLoader_hpp
#define AnimationLoader_hpp

#include <stdio.h>
#include <memory>
#include <unordered_map>

#include "Animation.hpp"

class ResourceManager;

class AnimationLoader
{
protected:
    std::unordered_map<std::string, std::weak_ptr<Animation>> _animations;
    ResourceManager* _resourceManager;
    
public:
    AnimationLoader(ResourceManager* resourceManager);
    virtual ~AnimationLoader();
    
    std::shared_ptr<Animation> GetAnimation(const std::string& name);
    std::shared_ptr<Animation> LoadAnimation(const std::string& name, const char *fullPath);
    
protected:
    void ClearExpiredAnimations();
};

#endif /* AnimationLoader_hpp */
