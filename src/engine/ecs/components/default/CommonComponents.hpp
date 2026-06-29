//
//  CommonComponents.hpp
//  EPet
//
//  Created by marina porkhunova on 27.01.2025.
//

#ifndef CommonComponents_hpp
#define CommonComponents_hpp

#include <stdio.h>
#include <iostream>

#include "Point.h"

#include "json.hpp"

using json = nlohmann::json;
struct Texture;


struct Sorting
{
    int layer;
    
    static Sorting Load(const json& data);
    static void Save(Sorting& obj, json& data);
};

struct UpdateSorting
{
    
};

struct Transform
{
    IPoint position = IPoint(0, 0);
    
    static Transform Load(const json& data);
    static void Save(Transform& obj, json& data);
};

struct Image
{
    std::string resoursesId;
    //std::shared_ptr<Texture> resource;
    
    static Image Load(const json& data);
    static void Save(Image& obj, json& data);
};

struct Animation;

struct Animator
{
    std::string resoursesId;
    std::shared_ptr<const Animation> animation;
    
    double timer = 0;
    int frame = 0;
    
    static Animator Load(const json& data);
    static void Save(Animator& obj, json& data);
};

struct AnimationFinished
{
    std::string resoursesId;
};

struct AnimationFinished_OF /// one shot
{
    std::string resoursesId;
};

struct RendererObject
{
    std::shared_ptr<Texture> resource;
    static RendererObject Load(const json& data);
    static void Save(RendererObject& obj, json& data);
};

#include "IFontLoader.hpp"
class TextUpdateSystem;

struct Text
{
private:
    std::string text;
    std::shared_ptr<Font> font;
    FontSettings settings;
    
public:
    static Text Load(const json& data);
    static void Save(Text& obj, json& data);
    
    friend TextUpdateSystem;
};

struct SetNewText
{
    std::string text;
};

struct SetNewFont
{
    std::string fontName;
};

struct NeedUpdateText // if smth changed in settings/text/font
{
};

#endif /* CommonComponents_hpp */
