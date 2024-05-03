//
//  IWindow.h
//  EPet
//
//  Created by marina porkhunova on 03.05.2024.
//

#ifndef IWindow_h
#define IWindow_h

#define WINDOW_DEFAULT_WIDTH 320
#define WINDOW_DEFAULT_HEIGHT 240
#define WINDOW_DEFAULT_TITLE "[Window]"

class IWindow
{
public:
    IWindow() = default;
    virtual ~IWindow() = default;
    
    /// return true if creating was success
    virtual bool CreateWindow(int width = WINDOW_DEFAULT_WIDTH,
                              int height = WINDOW_DEFAULT_WIDTH,
                              const char *title = WINDOW_DEFAULT_TITLE) = 0;
    
    virtual void HandleEvent() = 0;
    
    virtual int GetHeight() = 0;
    virtual int GetWidth() = 0;
    
    // TODO: has focus;
    // TODO: smth with render;
};
#endif /* IWindow_h */
