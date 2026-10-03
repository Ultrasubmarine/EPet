//  TextSystem.cpp
//  EPet
//
//  Создано по аналогии с RenderSystem.cpp
//

#include "TextUpdateSystem.hpp"
#include "Game.hpp"
#include "IRender.h"
#include "ResourceManager.hpp"

SYSTEM_CPP(TextUpdateSystem);

void TextUpdateSystem::Init()
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

void TextUpdateSystem::Update(double dt)
{
    if(!_resourceManager)
    {
        return;
    }
    
    UpdateText();
    UpdateFont();
    UpdateRenderTexture();
}

void TextUpdateSystem::UpdateText()
{
    //Set text
    for(auto [entt, textImage, newText] :_registry.view<Text, SetNewText>().each())
    {
        if(textImage.text.compare(newText.text) == 0) {
            continue;
        }
        
        textImage.text = newText.text;
        _registry.emplace_or_replace<NeedUpdateText>(entt);
    }
    
    _registry.clear<SetNewText>();
}

void TextUpdateSystem::UpdateFont()
{
    for(auto [entt, text, newFont] :_registry.view<Text, SetNewFont>().each())
    {
        if (text.font && text.font->name.compare(newFont.fontName) == 0) {
            continue;
        }
    
        auto font = _resourceManager->GetFont(newFont.fontName);
        text.font = font;
        _registry.emplace_or_replace<NeedUpdateText>(entt);
    }
    
    _registry.clear<SetNewFont>();
}

void TextUpdateSystem::UpdateFontSetting()
{
    for(auto [entt, text, newSettings] :_registry.view<Text, SetNewFontSettings>().each())
    {
        if (text.settings == newSettings.settings) {
            continue;
        }
        
        text.settings = newSettings.settings;
        _registry.emplace_or_replace<NeedUpdateText>(entt);
        
    }
    _registry.clear<SetNewFontSettings>();
    
}

void TextUpdateSystem::UpdateRenderTexture()
{
    //Update render object
    for(auto [entt, text, rObj] :_registry.view<Text, RendererObject, NeedUpdateText>().each())
    {
        auto newImage = _resourceManager->GetTextTexture(text.text, text.font, text.settings);
        rObj.resource = newImage;
    }
    
    _registry.clear<NeedUpdateText>();
}
