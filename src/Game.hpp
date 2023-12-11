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

struct PetAvatar
{
    std::string view = "-----------------\n\n\n       ^  ^\n      (. .)          \n\n   I'm awake :)\n\n-----------------";

};

class Game
{
public:
    enum State
    {
        Active,
        Wait
    };
    
    Game();
    ~Game();
    
    void Loop();
    
    //TODO active list
    PetAvatar* _avatar;
        
    //TODO passive list
    Timer *_timer;
    RequestList *_requestList;
    Schedule *_schedule;
    
private:
    State _currentState;
    
    inline void LoadActiveObjects();
    inline void UploadActiveObjects();
    
public:
    void SetState(State newState);
    
};
#endif /* Game_hpp */
