//
//  Input.cpp
//  EPet
//
//  Created by marina porkhunova on 12.01.2024.
//

#include "Input.hpp"
using time_point = std::chrono::steady_clock::time_point;
//#if defined(__GNUG__) || defined(__GNUC__)
//#define OS_LINUX
//#elif defined(_MAC)
//#define OS_MAC
//#elif defined(_WIN32)
//#define OS_WIN
//#endif
//
//
//#ifdef OS_WIN
//#include <conio.h>
//#elif defined(OS_LINUX) || defined(OS_MAC)
//#include <unistd.h>
//#include <sys/socket.h>
//#endif

//bool StdinHasData()
//{
//#   if defined(OS_WIN)
//    // this works by harnessing Windows' black magic:
//    return _kbhit();
//#   elif defined(OS_LINUX) || defined(OS_MAC)
//    // using a timeout of 0 so we aren't waiting:
//    struct timespec timeout{ 0l, 0l };
//
//    // create a file descriptor set
//    fd_set fds{};
//
//    // initialize the fd_set to 0
//    FD_ZERO(&fds);
//    // set the fd_set to target file descriptor 0 (STDIN)
//    FD_SET(0, &fds);
//
//    // pselect the number of file descriptors that are ready, since
//    //  we're only passing in 1 file descriptor, it will return either
//    //  a 0 if STDIN isn't ready, or a 1 if it is.
//    return pselect(0 + 1, &fds, nullptr, nullptr, &timeout, nullptr) == 1;
//#   else
//    // throw a compiler error
//    static_assert(false, "Failed to detect a supported operating system!");
//#   endif
//}


#include <SDL2/SDL.h>
#include <iostream>


#include <map>
#include <vector>

void PrintKeyInfo( SDL_KeyboardEvent *key );

Input::Input()
{
    _bindingKeys = {
        {KeyCode::A, "BUTTON_A"},
        {KeyCode::B, "BUTTON_B"},
        {KeyCode::D, "BUTTON_D"}
    };
}

void Input::AddInput(KeyCode code, KeyState state)
{
    InputInfo info;
    info.Code = code;
    info.State = state;
    info.Time = std::chrono::steady_clock::now();
 
    _keyBuffer.push_back(info);
}

void Input::Update()
{
    //clear all previous events
    _eventsPool.clear();
    
    //check simple keys
    for(auto& i: _keyBuffer)
    {
        auto name = GetKeyName(i.Code);
        if(!name.empty()){
            _eventsPool.push_back(KeyEvent{name, i.State});
        }
    }
    _keyBuffer.clear();
}

std::string Input::GetKeyName(KeyCode keyCode)
{
    if(auto it = _bindingKeys.find(keyCode); it != _bindingKeys.end())
    {
        return (*it).second;
    }
    return {};
}

void Input::BindKey(KeyCode keyCode, std::string keyName)
{
    _bindingKeys[keyCode] = keyName;
}

void Input::UnbindKey(KeyCode keyCode)
{
    _bindingKeys.erase(keyCode);
}

void Input::UnbindKey(std::string keyName)
{
    auto it = _bindingKeys.begin();
    while(it != _bindingKeys.end())
    {
        if(it->second == keyName)
        {
            break;
        }
        it++;
    }
    
    if(it != _bindingKeys.end())
    {
        _bindingKeys.erase(it);
    }
}

void Input::UnbindAllKeys()
{
    _bindingKeys.clear();
}
