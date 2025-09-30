//
//  Game.hpp
//  EPet
//
//  Created by marina porkhunova on 27.11.2023.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include "Singleton.hpp"

class IWindow;
class IRender;

class FrameRate;
class SceneManager;
class ResourceManager;

class PlayerSave;

class Game final: public Singleton<Game>
{
public:
    Game() = default;
    ~Game();
    
    Game(const Game& ) = delete;
    Game(Game&&) = delete;
    
    bool Init(); /// true - if init was successful
    void Deinit();
    void Loop();
    
    ResourceManager* GetResourceManager() { return _resourceManager;};
    IRender* GetRender() { return _render;};
    
private:
    void Input();
    void RenderAll();
    
private:
    IWindow *_window = nullptr;
    IRender *_render = nullptr;
    
    FrameRate *_frameRate = nullptr;
    SceneManager *_sceneManager = nullptr;
    ResourceManager *_resourceManager = nullptr;
    
    PlayerSave* _playerSave = nullptr; // TODO: temp place
};
#endif /* Game_hpp */
