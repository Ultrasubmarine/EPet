//
//  IRender.hpp
//  EPet
//
//  Created by marina porkhunova on 03.08.2024.
//

#ifndef IRender_h
#define IRender_h

#include <stdio.h>
#include "IWindow.h"

struct Rect;
//struct Rect
//{
//    int x,y;
//    int w,h;
//};

class IRender
{
public:
    virtual ~IRender() {};
    virtual void* Init(IWindow* w) = 0;
    virtual void Deinit() = 0;
    
    virtual void Clear() = 0;
    virtual void Draw( /*what*/ Rect& source, Rect& windRect) = 0;
    virtual void Present() = 0;
    
    virtual bool IsRenderExist() = 0;
};

#endif /* IRender_h */
