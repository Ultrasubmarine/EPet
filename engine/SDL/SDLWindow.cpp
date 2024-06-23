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

SDLWindow::SDLWindow()
{
}

SDLWindow::~SDLWindow()
{
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

bool SDLWindow::CreateWindow(int width, int height, const char *title)
{
    if( SDL_Init(SDL_INIT_EVERYTHING ^ SDL_INIT_AUDIO))
    {
       // LOG_ERROR("Window::CreateWindow(): SDL_Init() error");
        return false;
    }
    
    _window = SDL_CreateWindow(title,
                     SDL_WINDOWPOS_UNDEFINED,
                     SDL_WINDOWPOS_UNDEFINED,
                     width, height,
                     SDL_WINDOW_RESIZABLE);
    if(!_window)
    {
        return false;
      //  LOG_ERROR("Window::CreateWindow(): Fail creating window");
    }
    return true;
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
