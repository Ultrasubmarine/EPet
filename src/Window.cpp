//
//  Window.cpp
//  Labirint
//
//  Created by marina porkhunova on 18.02.2023.
//

#include "Window.hpp"
#include "Debug.h"


Window::~Window()
{
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

Window::Window(const json* settings)
{
    LoadSettings(settings);
    CreateWindow();
    return;
}

void Window::LoadSettings(const json* settings)
{
    if(settings && (*settings).contains("window"))
    {
        auto& windows_settings = (*settings)["window"];
        
        _title = windows_settings["name"].get<std::string>();
        _width = windows_settings["screen"]["width"].get<int>();
        _height = windows_settings["screen"]["height"].get<int>();
    }
    else
    {
        LOG_EXEPTION("Window Settings not found. Used default settings");
        
        _title = Window::DEFAULT_TITLE;
        _width = Window::DEFAULT_WIDTH;
        _height = Window::DEFAULT_HEIGHT;
    }
}

void Window::CreateWindow()
{
    if( SDL_Init(SDL_INIT_EVERYTHING ^ SDL_INIT_AUDIO))
    {
        LOG_ERROR("Window::CreateWindow(): SDL_Init() error");
        return ;
    }
    
    _window = SDL_CreateWindow(_title.c_str(),
                     SDL_WINDOWPOS_UNDEFINED,
                     SDL_WINDOWPOS_UNDEFINED,
                     _width, _height,
                     SDL_WINDOW_RESIZABLE);
    
    if(!_window)
    {
        LOG_ERROR("Window::CreateWindow(): Fail creating window");
    }
}
