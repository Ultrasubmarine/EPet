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

    for (const auto& levelData : *from)
    {
        if (!levelData.is_object() || !levelData.contains("level") || !levelData["level"].is_number_integer())
        {
            LOG_ERROR("HamsterAnimationDictionary::Load() entry without integer \"level\" was skipped");
            continue;
        }

        const int level = levelData["level"].get<int>();
        if (level < 0)
        {
            LOG_ERROR("HamsterAnimationDictionary::Load() negative level [" << level << "] was skipped");
            continue;
        }

        if (!levelData.contains("animations") || !levelData["animations"].is_object())
        {
            LOG_ERROR("HamsterAnimationDictionary::Load() level [" << level << "] doesn't have \"animations\" object");
            continue;
        }

        if (level >= (int)_data.size())
        {
            _data.resize(level + 1);
        }

        auto& tags = _data[level];
        if (!tags.empty())
        {
            LOG_ERROR("HamsterAnimationDictionary::Load() level [" << level << "] is duplicated. Second entry was skipped");
            continue;
        }

        const auto& animations = levelData["animations"];
        for (auto it = animations.begin(); it != animations.end(); ++it)
        {
            if (!it.value().is_string())
            {
                LOG_MESSAGE("HamsterAnimationDictionary::Load() incorrect animation name for tag [" << it.key() << "] level [" << level << "]");
                continue;
            }

            auto name = it.value().get<std::string>();
            if (auto animation = resourceManager->GetAnimation(name))
            {
                tags[it.key()] = animation;
            }
            else
            {
                LOG_ERROR("HamsterAnimationDictionary::Load() animation [" << name << "] for tag [" << it.key() << "] level [" << level << "] didn't load");
            }
        }
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
