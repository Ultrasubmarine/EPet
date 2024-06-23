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

class Input: public Singleton<Input>
{   
private:
    /// struct-helper containing not yet analized input
    struct InputInfo
    {
        KeyCode Code;
        KeyState State;
        time_point Time;
    };
    
    std::vector<KeyEvent> _eventsPool;
    
    std::vector<InputInfo> _unprocessedKeys;
    std::map<KeyCode, std::string > _listeningKeys;
public:
    Input();
    ~Input() = default;
    
    void Update();
    void AddInput(KeyCode, KeyState);
    
    void BindKey(KeyCode keyCode, std::string keyName);
    void UnbindKey(std::string keyName);
    
    const std::vector<KeyEvent>& GetEvents() const { return _eventsPool;};
    std::string GetKeyName(KeyCode);
};
#endif /* Input_hpp */
