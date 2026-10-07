//
//  GameSettings.cpp
//  EPet
//
//  Created by marina porkhunova on 07.10.2026.
//

#include "GameSettings.hpp"

#include "Logger.hpp"

GameSettings GameSettings::Load(const json* data)
{
    GameSettings settings;
    if(!data) {
        return settings;
    }
    
    
    // TODO: read "window": {"name", "screen": {"width", "height"}}, "fps", "main_scene"; keep defaults for missing fields

    return settings;
}
