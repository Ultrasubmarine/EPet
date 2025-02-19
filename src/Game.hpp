//
//  Game.hpp
//  EPet
//
//  Created by marina porkhunova on 27.11.2023.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>

class IWindow;
class IRender;

class FrameRate;
class SceneManager;
class ResourceManager;

class Game
{
private:
    void CheckInput();
public:
    Game() = default;
    ~Game();
    
    bool Init(); /// true - if init waa successful
    void Deinit();
    void Loop();
    
    ResourceManager* GetResourceManager() { return _resourceManager;};
private:
    IWindow *_window = nullptr;
    IRender *_render = nullptr;
    
    FrameRate *_frameRate = nullptr;
    SceneManager *_sceneManager = nullptr;
    ResourceManager *_resourceManager = nullptr;
};
#endif /* Game_hpp */
