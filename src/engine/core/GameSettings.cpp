//
//  GameSettings.cpp
//  EPet
//
//  Created by marina porkhunova on 07.10.2026.
//

#include "GameSettings.hpp"

#include "Logger.hpp"
#include "JsonUtils.hpp"

GameSettings GameSettings::Load(const json* data)
{
    GameSettings settings;
    if(!data) {
        LOG_WARNING("settings data is empty. all values are default");
        return settings;
    }

    ReadValue(*data, "/window/name", settings._title);
    ReadValue(*data, "/window/screen/width", settings._width);
    ReadValue(*data, "/window/screen/height", settings._height);
    ReadValue(*data, "/fps", settings._fps);
    ReadValue(*data, "/main_scene", settings._startScene);

    const GameSettings defaults;
    if(settings._width <= 0 || settings._height <= 0) {
        LOG_WARNING("invalid window size " << settings._width << "x" << settings._height << ". use default");
        settings._width = defaults._width;
        settings._height = defaults._height;
    }
    if(settings._fps <= 0) {
        LOG_WARNING("invalid fps " << settings._fps << ". use default");
        settings._fps = defaults._fps;
    }

    return settings;
}
