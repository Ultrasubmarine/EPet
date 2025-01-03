//
//  Game.hpp
//  EPet
//
//  Created by marina porkhunova on 27.11.2023.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>


class FrameRate;

class IWindow;
class IRender;

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
    
private:
    IWindow *_window;
    IRender *_render;
    FrameRate *_frameRate;
};
#endif /* Game_hpp */
