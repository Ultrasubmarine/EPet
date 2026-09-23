//
//  HamsterAnimationDictionary.hpp
//  EPet
//
//  Created by marina porkhunova on 14.09.2026.
//

#ifndef HamsterAnimationDictionary_hpp
#define HamsterAnimationDictionary_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <memory>
#include <string>

#include "json.hpp"

using json = nlohmann::json;

struct Animation;
class ResourceManager;

/// data[level][tag] -> animation
class HamsterAnimationDictionary
{
public:
    void Load(ResourceManager* resourceManager, json* from);

    std::shared_ptr<const Animation> Get(int level, const std::string& tag) const;

private:
    std::vector<std::map<std::string, std::shared_ptr<const Animation>>> _data;
};

#endif /* HamsterAnimationDictionary_hpp */
