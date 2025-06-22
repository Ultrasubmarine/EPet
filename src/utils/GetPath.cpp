//
//  GetPath.cpp
//  Labirint
//
//  Created by marina porkhunova on 07.01.2023.
//

#include "GetPath.hpp"

char* GetPath_Apple(CFStringRef name, CFStringRef type)
{
    CFURLRef manifest_url = CFBundleCopyResourceURL(CFBundleGetMainBundle(),
                                                    name, type,
                                                    NULL);
    char * manifest_path = (char *)malloc(PATH_MAX);
    CFURLGetFileSystemRepresentation(manifest_url, true, (uint8_t *)manifest_path, PATH_MAX);
    
    if (manifest_url != NULL)
        {
          CFRelease(manifest_url);
        }
    return manifest_path;
}

char* GetPath(std::string& title, std::string& type)
{
#ifdef __APPLE__
    CFStringRef p_name = CFStringCreateWithCString(NULL, title.c_str(), NULL);
    CFStringRef p_type = CFStringCreateWithCString(NULL, type.c_str(), NULL);
    return GetPath_Apple(p_name, p_type);
#endif
        return NULL;
}
