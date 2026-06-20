//  TextSystem.cpp
//  EPet
//
//  Создано по аналогии с RenderSystem.cpp
//

#include "TextLoadSystem.hpp"
#include "Game.hpp"
#include "IRender.h"
#include "ResourceManager.hpp"

SYSTEM_CPP(TextLoadSystem);

void TextLoadSystem::Init()
{
    _resourceManager = Game::Instance().GetResourceManager();
    
    if(!_resourceManager)
    {
        return;
    }
    for(auto [entt, text, rObj] :_registry.view<Text, RendererObject>().each())
    {
        if(text.text.empty()) {
            continue;
        }
        
        rObj.resource = _resourceManager->GetTextTexture(text.text, text.font, text.settings);
    }
}

void TextLoadSystem::Update(double dt)
{
    if(!_resourceManager)
    {
        return;
    }
    
    //Set text
    for(auto [entt, textImage, newText, rObj] :_registry.view<Text, SetTextImage, RendererObject>().each())
    {
        if(textImage.text.compare(newText.text) == 0) {
            continue;
        }
        textImage.text = newText.text;
        auto newImage = _resourceManager->GetTextTexture(textImage.text, textImage.font, textImage.settings);
        rObj.resource = newImage;
    }
    _registry.clear<SetTextImage>();
}
