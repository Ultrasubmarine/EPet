//
//  CommonComponents.cpp
//  EPet
//
//  Created by marina porkhunova on 07.07.2025.
//

#include <stdio.h>
#include <algorithm>
#include <array>

#include "CommonComponents.hpp"
#include "Game.hpp"
#include "ResourceManager.hpp"
#include "JsonUtils.hpp"
#include "PointJSON.hpp"


Transform Transform::Load(const json& data)
{
    Transform obj;

    ReadOptionalValue<Point<int>>(data, "/position", obj.position);
    return obj;
}

void Transform::Save(Transform& obj, json& data)
{
    WriteValue<Point<int>>(data, "/position", obj.position);
}

Sorting Sorting::Load(const json& data)
{
    Sorting obj;
    
    ReadValue<int>(data, "/layer", obj.layer);
    return obj;
}

void Sorting::Save(Sorting& obj, json& data)
{
    WriteValue<int>(data, "/layer", obj.layer);
}

Image Image::Load(const json& data)
{
    Image obj;
    
    ReadValue<std::string>(data, "/imageId", obj.resoursesId);
    return obj;
    
    //TODO: Load resource callback;
   // obj.resource = Game::Instance().GetResourceManager()->GetTexture(obj.resoursesId);
}
    
void Image::Save(Image& obj, json& data)
{
    WriteValue<std::string>(data, "/imageId", obj.resoursesId);
}


Animator Animator::Load(const json& data)
{
    Animator obj;
    ReadOptionalValue<std::string>(data, "/animationId", obj.resoursesId);

    if(!obj.resoursesId.empty())
    {
        //TODO: Load resource callback;
        obj.animation = Game::Instance().GetResourceManager()->GetAnimation(obj.resoursesId);
    }
    return obj;
}

void Animator::Save(Animator& obj, json& data)
{
    WriteValue<std::string>(data, "/animationId", obj.resoursesId);
}


RendererObject RendererObject::Load(const json& data)
{
    RendererObject obj;
    return obj;
}

void RendererObject::Save(RendererObject& obj,  json& data)
{
    // skip
}

Text Text::Load(const json& data)
{
    Text obj;
    ReadOptionalValue<std::string>(data, "/text", obj.text);
    ReadOptionalValue<int>(data, "/size", obj.settings.size);
    
    if(std::array<int, 3> color; ReadOptionalValue<std::array<int, 3>>(data, "/color", color))
    {
        obj.settings.color = {
            (std::uint8_t)std::clamp(color[0], 0, 255),
            (std::uint8_t)std::clamp(color[1], 0, 255),
            (std::uint8_t)std::clamp(color[2], 0, 255)
        };
    }
    
    std::string fontName = DEFAULT_FONT;
    ReadOptionalValue<std::string>(data, "/font", fontName);
    
    //TODO: Load resource callback;
    obj.font = Game::Instance().GetResourceManager()->GetFont(fontName);
   // obj.resource = Game::Instance().GetResourceManager()->GetTextTexture(obj.text, obj.font, obj.settings);
    return obj;
}
    
void Text::Save(Text& obj, json& data)
{
   // skip for now
}

