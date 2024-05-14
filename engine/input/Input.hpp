//
//  Input.hpp
//  EPet
//
//  Created by marina porkhunova on 12.01.2024.
//

#ifndef Input_hpp
#define Input_hpp

#include <string>
#include <vector>
#include <chrono>
#include <map>

#include "Singleton.hpp"
#include "InputEvents.h"

#include "EngineSettings.h"

using time_point = std::chrono::steady_clock::time_point;

class Input: public Singleton<Input>
{   
    std::vector<VirtualKeyEvent> _eventsPool;
    
    std::vector<KeyEventInfo> _unprocessedInput;    
    std::map<InputKey, std::string> _listeningKeys;
  //  std::map<InputAccords, std::string> _listeningAccords;
    
    
    //key accords
    bool _isAccordsEnable = false;
    std::chrono::steady_clock::time_point _delayForAccord;
    
public:
    Input();
    ~Input() = default;
    
    void AddEvent(InputKey, KeyState state);
    void Update();
    
    void AddListeningKey(InputKey key, std::string name);
    void RemoveListeningKey(std::string name);
    
    const std::vector<VirtualKeyEvent>& GetEvents() const { return _eventsPool;};
};
#endif /* Input_hpp */
