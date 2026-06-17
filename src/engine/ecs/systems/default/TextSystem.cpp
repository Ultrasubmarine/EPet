//  TextSystem.cpp
//  EPet
//
//  Создано по аналогии с RenderSystem.cpp
//

#include "TextSystem.hpp"
#include "Game.hpp"
#include "IRender.h"
#include "ResourceManager.hpp"

SYSTEM_CPP(TextSystem);

void TextSystem::Init()
{
    _resourceManager = Game::Instance().GetResourceManager();
}

void TextSystem::Update(double dt)
{
    for(auto [entt, textImage, newText] :_registry.view<TextImage, SetTextImage>().each())
    {
        if(textImage.text.compare(newText.text) == 0) {
            continue;
        }
        textImage.text = newText.text;
        auto newImage = _resourceManager->GetTextTexture(textImage.text, textImage.font, textImage.settings);
        textImage.resource = newImage;
    }
    _registry.clear<SetTextImage>();
}
