//
//  Game.hpp
//  EPet
//
//  Created by marina porkhunova on 27.11.2023.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <string>
#include <memory>

#include "Singleton.hpp"

class IWindow;
class IRender;

class FrameRate;
class SceneManager;
class ResourceManager;

class PlayerSave;
class GameSettings;

class Game final: public Singleton<Game>
{
public:
    Game();
    ~Game();
    
    Game(const Game& ) = delete;
    Game(Game&&) = delete;
    
    bool Init(); /// true - if init was successful
    void Start(); /// after init() but before Loop()
    void Deinit();

    void Loop();
    
    SceneManager* GetSceneManager() { return _sceneManager;};
    ResourceManager* GetResourceManager() { return _resourceManager;};
    IRender* GetRender() { return _render;};
    PlayerSave* GetPlayerSave() { return _playerSave;};
    
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
    
    std::unique_ptr<GameSettings> _settings = nullptr;
    const std::string _gameSettingsFileName = "game_settings";
};
#endif /* Game_hpp */
