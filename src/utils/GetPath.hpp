//
//  GetPath.hpp
//  Labirint
//
//  Created by marina porkhunova on 07.01.2023.
//

#ifndef GetPath_hpp
#define GetPath_hpp

#include <stdio.h>

#include <string>
#include <CoreFoundation/CoreFoundation.h>

/// use free() to returned string
char* GetPath(const std::string& title, const std::string* type = nullptr /* for directory searching */);

//use free() to returned string
char* GetPath_Apple(CFStringRef name, CFStringRef type);


#endif /* GetPath_hpp */
