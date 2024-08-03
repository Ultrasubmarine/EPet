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

class IWindow;
class IRender;

class Game
{
private:
    void CheckInput();
    
public:    
    Game();
    ~Game();
    
    void Loop();
    
    IWindow *_window;
    IRender *_render;
    
    //tmp old hamster core stuff. need to move in other place
    Timer *_timer;
    RequestList *_requestList;
    Schedule *_schedule;
    FrameRate *_frameRate;
};
#endif /* Game_hpp */
