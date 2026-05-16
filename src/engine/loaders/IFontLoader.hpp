//
//  FontLoader.hpp
//  Labirint
//
//  Created by marina porkhunova on 25.02.2023.
//

#ifndef IFontLoader_hpp
#define IFontLoader_hpp

#include <stdio.h>
#include <unordered_map>

#include "Font.hpp"

#define DEFAULT_FONT "Roboto-Light"

struct RGBA
{
    std::uint8_t r{};
    std::uint8_t g{};
    std::uint8_t b{};
    std::uint8_t a{255};
};

struct FontSettings
{  
    int size;
    RGBA color;
};

struct Texture;

class IFontLoader
{
    std::unordered_map<std::string, std::shared_ptr<Font>> _fonts;
    
public:
    virtual ~IFontLoader() {};
    
 //  /// doesn't storage
 //   std::shared_ptr<TextTexture> GetText(std::string& text, std::shared_ptr<Font> font, int fsize, SDL_Color color);
    
    std::shared_ptr<Font> GetFont(const std::string& name);
    std::shared_ptr<Font> LoadFont(const std::string& name, const char *fullPath);
    virtual std::shared_ptr<Texture> GetTexture(std::string& text, std::shared_ptr<Font> font, const FontSettings& settings) = 0;
    
    void DeleteFont(Font* font);
    void DeleteFont(const std::string& fontName);
    
protected:
    /// different libs could have different realisation for loading textures
    virtual Font* _LoadFont(const std::string& name, const char *fullPath) = 0;
    
};


#endif /* FontLoader_hpp */
