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

class Timer;
class Schedule;
class RequestList;
class View;
class FrameRate;
class Input;

class Game
{
private:
    void CheckInput(Input* i);
    
public:    
    Game();
    ~Game();
    
    void Loop(Input* i);
        
    Timer *_timer;
    RequestList *_requestList;
    Schedule *_schedule;
    View *_view;
    FrameRate *_frameRate;
};
#endif /* Game_hpp */
