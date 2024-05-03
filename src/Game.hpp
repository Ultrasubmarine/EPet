//
//  Game.hpp
//  EPet
//
//  Created by marina porkhunova on 27.11.2023.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>

class Timer;
class Schedule;
class RequestList;
class View;
class FrameRate;
class SDLWindow;
class Input;

class Game
{
private:
    void CheckInput();
    
public:    
    Game();
    ~Game();
    
    void Loop();
    
    SDLWindow *_window;
    Timer *_timer;
    RequestList *_requestList;
    Schedule *_schedule;
    FrameRate *_frameRate;
    Input *_input;
};
#endif /* Game_hpp */
