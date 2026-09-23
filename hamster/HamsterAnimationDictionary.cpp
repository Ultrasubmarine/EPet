//
//  HamsterAnimationDictionary.cpp
//  EPet
//
//  Created by marina porkhunova on 14.09.2026.
//

#include "HamsterAnimationDictionary.hpp"

#include "ResourceManager.hpp"
#include "Logging.hpp"

void HamsterAnimationDictionary::Load(ResourceManager* resourceManager, json* from)
{
    if (!resourceManager)
    {
        LOG_ERROR("HamsterAnimationDictionary::Load() empty ResourceManager. Impossible to load animations");
        return;
    }

    if (!from || !from->is_array())
    {
        LOG_ERROR("HamsterAnimationDictionary::Load() manifest json is missing or is not an array of levels");
        return;
    }

    _data.clear();
    _data.reserve(from->size());

    for (const auto& levelData : *from)
    {
        std::map<std::string, std::shared_ptr<const Animation>> tags;

        if (levelData.is_object())
        {
            for (auto it = levelData.begin(); it != levelData.end(); ++it)
            {
                if (!it.value().is_string())
                {
                    LOG_MESSAGE("HamsterAnimationDictionary::Load() incorrect animation name for tag [" << it.key() << "]");
                    continue;
                }

                auto name = it.value().get<std::string>();
                if (auto animation = resourceManager->GetAnimation(name))
                {
                    tags[it.key()] = animation;
                }
                else
                {
                    LOG_ERROR("HamsterAnimationDictionary::Load() animation [" << name << "] for tag [" << it.key() << "] didn't load");
                }
            }
        }

        _data.push_back(std::move(tags));
    }
}

std::shared_ptr<const Animation> HamsterAnimationDictionary::Get(int level, const std::string& tag) const
{
    if (level < 0 || level >= (int)_data.size())
    {
        LOG_ERROR("HamsterAnimationDictionary::Get() level [" << level << "] is out of range");
        return nullptr;
    }

    const auto& tags = _data[level];
    if (auto it = tags.find(tag); it != tags.end())
    {
        return it->second;
    }

    LOG_ERROR("HamsterAnimationDictionary::Get() tag [" << tag << "] not found for level [" << level << "]");
    return nullptr;
}
