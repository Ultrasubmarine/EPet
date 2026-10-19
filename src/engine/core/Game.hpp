//
//  Game.hpp
//  EPet
//
//  Created by marina porkhunova on 27.11.2023.
//

#ifndef Game_hpp
#define Game_hpp

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
    Game();
    ~Game();

public:
    Game(const Game& ) = delete;
    Game(Game&&) = delete;
    
    bool Init(); /// true - if init was successful
    void Start(); /// after init() but before Loop()
    void Deinit();

    void Loop();
    
    SceneManager* GetSceneManager() const { return _sceneManager.get();}
    ResourceManager* GetResourceManager() const { return _resourceManager.get();}
    IRender* GetRender() const { return _render.get();}
    PlayerSave* GetPlayerSave() const { return _playerSave.get();}
    
private:
    void HandleInput();
    
private:
//systems
    std::unique_ptr<IWindow> _window;
    std::unique_ptr<IRender> _render;
    
    std::unique_ptr<FrameRate> _frameRate;
    std::unique_ptr<SceneManager> _sceneManager;
    std::unique_ptr<ResourceManager> _resourceManager;
    
//save
    std::unique_ptr<PlayerSave> _playerSave;
    
//settings
    std::unique_ptr<GameSettings> _settings;
    const std::string _gameSettingsFileName = "game_settings";

    friend class Singleton<Game>;
};
#endif /* Game_hpp */
