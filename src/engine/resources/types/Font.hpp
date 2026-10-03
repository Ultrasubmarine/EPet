//
//  Font.hpp
//  EPet
//
//  Created by marina porkhunova on 11.05.2026.
//

#ifndef Font_hpp
#define Font_hpp

#include <stdio.h>
#include <string>
#include <variant>

struct SDLFont;

struct Font
{
    std::string name;
    std::variant<std::unique_ptr<SDLFont>> resource;
    
    Font(const std::string& name, std::unique_ptr<SDLFont> res_SDL);
    Font(const char* name, std::unique_ptr<SDLFont> res_SDL);
    
    ~Font();
    
    // no copy
    Font(Font& other) = delete;
    Font& operator=(const Font& other) = delete;
    
    //no move
    Font(Font&& other) = delete;
    Font& operator=(const Font&& other) = delete;
};
#endif /* Font_hpp */
