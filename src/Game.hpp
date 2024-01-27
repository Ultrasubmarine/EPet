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

class Game
{
private:
    void CheckInput();
    
public:    
    Game();
    ~Game();
    
    void Loop();
        
    Timer *_timer;
    RequestList *_requestList;
    Schedule *_schedule;
    FrameRate *_frameRate;
    
    //tmp
    View *_view;
};
#endif /* Game_hpp */
