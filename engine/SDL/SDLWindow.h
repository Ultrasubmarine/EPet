//
//  Window.hpp
//  Labirint
//
//  Created by marina porkhunova on 18.02.2023.
//

#ifndef Window_hpp
#define Window_hpp

#include "IWindow.h"

class SDL_Window;

class SDLWindow : public IWindow
{
    SDL_Window* _window;
    
public:
    SDLWindow();
    virtual ~SDLWindow();

    bool CreateWindow(int width = WINDOW_DEFAULT_WIDTH,
                      int height = WINDOW_DEFAULT_WIDTH,
                      const char *title = WINDOW_DEFAULT_TITLE) override;
    
    void HandleEvent() override;

    int GetHeight() const override;
    int GetWidth() const override;
};
#endif /* Window_hpp */
