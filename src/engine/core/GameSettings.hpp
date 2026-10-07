//
//  GameSettings.hpp
//  EPet
//
//  Created by marina porkhunova on 07.10.2026.
//

#ifndef GameSettings_hpp
#define GameSettings_hpp

#include <string>

#include "json.hpp"
#include "IWindow.h"

using json = nlohmann::json;

class GameSettings
{
public:
    /// if data == nullptr  => all values are default
    static GameSettings Load(const json* data);

    const std::string& GetTitle() const { return _title; }
    int GetWidth() const { return _width; }
    int GetHeight() const { return _height; }
    int GetFps() const { return _fps; }
    const std::string& GetStartScene() const { return _startScene; }

private:
    std::string _title = WINDOW_DEFAULT_TITLE;
    int _width = WINDOW_DEFAULT_WIDTH;
    int _height = WINDOW_DEFAULT_HEIGHT;
    int _fps = 60;
    std::string _startScene;
};

#endif /* GameSettings_hpp */
