//
//  Font.cpp
//  EPet
//
//  Created by marina porkhunova on 11.05.2026.
//

#include "Font.hpp"
#include "SDLFont.h"


Font::Font(const std::string& name, std::unique_ptr<SDLFont> SDLres):
    name(name),
    resource(std::move(SDLres))
{};

Font::Font(const char* name, std::unique_ptr<SDLFont> SDLres):
    name(name),
    resource(std::move(SDLres))
{};

Font::~Font() = default;
