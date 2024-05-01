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
#include <map>

struct KeyEvent
{
    enum State
    {
        Pressed,
        Released
    };
    
    std::string name;
    State state;
};

class Input
{   
    std::vector<KeyEvent> _eventsPool;
    std::map<int, std::string> _listeningKeys;
    
public:
    Input();
    ~Input() = default;
    
    void Update();
    
    // table wich contains listening keycode and name of virtual keys map<
 //   void SetVirtualKeys();
    
    const std::vector<KeyEvent>& Get() const { return _eventsPool;};
};
#endif /* Input_hpp */
