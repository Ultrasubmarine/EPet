//
//  GameSettings.cpp
//  EPet
//
//  Created by marina porkhunova on 07.10.2026.
//

#include "GameSettings.hpp"

#include "Logger.hpp"
#include "JsonUtils.hpp"


GameSettings::GameSettings(const json* data)
{
    if(!data) {
        LOG_WARNING("settings data is empty. all values are default");
        return;
    }

    ReadValue(*data, "/window/name", _title);
    ReadValue(*data, "/window/screen/width", _width);
    ReadValue(*data, "/window/screen/height", _height);
    ReadValue(*data, "/fps", _fps);
    ReadValue(*data, "/main_scene", _startScene);

    if(_width <= 0 || _height <= 0) {
        LOG_WARNING("invalid window size " << _width << "x" << _height << ". use default");
        _width = WINDOW_DEFAULT_WIDTH;
        _height = WINDOW_DEFAULT_HEIGHT;
    }
    
    if(_fps <= 0) {
        LOG_WARNING("invalid fps " << _fps << ". use default");
        _fps = DEFAULT_FPS;
    }
}
