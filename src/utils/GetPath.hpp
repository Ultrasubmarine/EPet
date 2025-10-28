//
//  GetPath.hpp
//  Labirint
//
//  Created by marina porkhunova on 07.01.2023.
//

#ifndef GetPath_hpp
#define GetPath_hpp

#include <stdio.h>
#include <filesystem>
#include <string>

#include <CoreFoundation/CoreFoundation.h>

namespace fs = std::filesystem;
//
///// use free() to returned string
inline char* GetPath(const std::string& title, const std::string* type = nullptr /* for directory searching */) {return nullptr;};

////use free() to returned string
//char* GetPath_Apple(CFStringRef name, CFStringRef type);
//

fs::path GetResourcePath();

fs::path GetSavePath();
#endif /* GetPath_hpp */
