//
//  SDLRender.hpp
//  EPet
//
//  Created by marina porkhunova on 03.08.2024.
//

#ifndef SDLRender_hpp
#define SDLRender_hpp

#include <stdio.h>
#include "IRender.h"

class SDL_Renderer;
class SDL_Rect;

using Rect = SDL_Rect;

class SDLRender: public IRender
{
    SDL_Renderer* _render;
    
   
public:
    
    ~SDLRender() override;
    void Init(IWindow* w) override; // simple SDLRender() ? 
    
    
    void Clear() override;
    void Draw(/* */Rect& source, Rect& windRect) override;
    void Present() override;
};

using Render = SDLRender;

#endif /* SDLRender_hpp */
