//
//  Window.cpp
//  Labirint
//
//  Created by marina porkhunova on 18.02.2023.
//

#include <stdio.h>
#include "SDLWindow.h"
#include "SDL2/SDL.h"

#include "Input.hpp"
#include "Logging.hpp"

SDLWindow::SDLWindow()
{
}

SDLWindow::~SDLWindow()
{
}

void* SDLWindow::CreateWindow(int width, int height, const char *title)
{
    if( SDL_Init(SDL_INIT_EVERYTHING ^ SDL_INIT_AUDIO))
    {
        LOG_ERROR("Window::CreateWindow(): SDL_Init() error");
        return nullptr;
    }
    
    _window = SDL_CreateWindow(title,
                     SDL_WINDOWPOS_UNDEFINED,
                     SDL_WINDOWPOS_UNDEFINED,
                     width, height,
                     SDL_WINDOW_RESIZABLE);
    if(!_window)
    {
        LOG_ERROR("Window::CreateWindow(): Fail creating window");
        return nullptr;
    
    }
    LOG_MESSAGE("Window::CreateWindow(): Window sucsesefull created");
    return _window;
}

void SDLWindow::DestroyWindow()
{
    if(_window)
    {
        SDL_DestroyWindow(_window);
        _window = nullptr;
        SDL_Quit();
    }
}

void SDLWindow::HandleEvent()
{
    SDL_Event event;
    if(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                break;
            case SDL_KEYDOWN:
            {
                auto keyCode = static_cast<KeyCode>(event.key.keysym.sym);
                Input::Instance().AddInput(keyCode, KeyState::Pressed);
                break;
            }
            case SDL_KEYUP:
            {
                auto key = static_cast<KeyCode>(event.key.keysym.sym);
                Input::Instance().AddInput(key, KeyState::Released);
                break;
            }
        }
    }
}

int SDLWindow::GetHeight() const
{
    return SDL_GetWindowSurface(_window)->w;
}

int SDLWindow::GetWidth() const
{
    return SDL_GetWindowSurface(_window)->h;
}

bool SDLWindow::IsWindowExist() const
{
    return _window != nullptr;
}
