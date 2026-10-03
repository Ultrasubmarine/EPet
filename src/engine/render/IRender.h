//
//  IRender.hpp
//  EPet
//
//  Created by marina porkhunova on 03.08.2024.
//

#ifndef IRender_h
#define IRender_h

#include <stdio.h>
#include <set>

#include "IWindow.h"

struct Texture;
class IWindow;

class IRender
{
public:
    virtual ~IRender() {};
    virtual void* Init(IWindow* w) = 0;
    virtual void Deinit() = 0;
    
    virtual void Clear() = 0;
    virtual void Draw(Texture* texture, const int& x, const int& y) = 0;
    virtual void Present() = 0;
    
    virtual bool IsRenderExist() = 0;
};

#endif /* IRender_h */
