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

class JsonLoader;
class ITextureLoader;

class AnimationLoader
{
protected:
    std::unordered_map<std::string, std::weak_ptr<Animation>> _animations;
    
    JsonLoader* _jsonLoader; // for loading json animation file
    ITextureLoader* _textureLoader; // for loading frames;
    
public:
    AnimationLoader(JsonLoader* loader);
    virtual ~AnimationLoader();
    
    std::shared_ptr<Animation> GetAnimation(const std::string& name);
    std::shared_ptr<Animation> LoadAnimation(const std::string& name, const char *fullPath);
    
protected:
    void DeleteAnimation(Animation* texture);
};

#endif /* AnimationLoader_hpp */
