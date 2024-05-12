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
//struct VirtualInputTable
//{
//    std::string name;
//    InputKey;
//};

class Input: public Singleton<Input>
{   
    std::vector<KeyEvent> _eventsPool;
    std::vector<std::pair<const InputKey,const time_point>> _unprocessedInput;
    
    std::map<InputKey, std::string> _listeningKeys;
    
    //key accords
    bool _isAccordsEnable = false;
    std::chrono::steady_clock::time_point _delayForAccord;
    
public:
    Input();
    ~Input() = default;
    
    void AddEvent(KeyEvent e);
    void Update();
    
 // table wich contains listening keycode and name of virtual keys map<
 //   void SetVirtualKeys();
    
    const std::vector<KeyEvent>& Get() const { return _eventsPool;};
};
#endif /* Input_hpp */
