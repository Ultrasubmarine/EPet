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

class SDLRender: public IRender
{
    SDL_Renderer* _render;
    
public:
    SDLRender() = default;
    ~SDLRender() override;
    
    void* Init(IWindow* w) override;
    void Deinit() override;
    
    void Clear() override;
    void Draw(Texture* texture, const int& x, const int& y) override; // TODO: add scale
    void Present() override;
    
    bool IsRenderExist() override;
    
    SDL_Renderer* GetRender() {return _render;};
};

using Render = SDLRender;

#endif /* SDLRender_hpp */
