//
//  GetPath.cpp
//  Labirint
//
//  Created by marina porkhunova on 07.01.2023.
//

#include "GetPath.hpp"

// from app bundle ONLY!
char* GetPath_Apple(CFStringRef name, CFStringRef type)
{
    CFURLRef manifest_url = CFBundleCopyResourceURL(CFBundleGetMainBundle(),
                                                    name, type,
                                                    NULL);
    
//    CFURLRef dir_url = CFBundleCopyResourceURL(CFBundleGetMainBundle(),
//                                               CFSTR("MyFolder"), // имя папки
//                                               NULL,              // расширение = NULL
//                                               NULL);
    
    char * manifest_path = (char *)malloc(PATH_MAX);
    CFURLGetFileSystemRepresentation(manifest_url, true, (uint8_t *)manifest_path, PATH_MAX);
    
    if (manifest_url != NULL)
        {
          CFRelease(manifest_url);
        }
    return manifest_path;
}

//char* GetPath_Apple(const std::string& name, CFStringRef type)
//{
//    CFURLRef manifest_url = CFBundleCopyResourceURL(CFBundleGetMainBundle(),
//                                                    CFSTR(name.c_str()), type,
//                                                    NULL);
//    
////    CFURLRef dir_url = CFBundleCopyResourceURL(CFBundleGetMainBundle(),
////                                               CFSTR("MyFolder"), // имя папки
////                                               NULL,              // расширение = NULL
////                                               NULL);
//    
//    char * manifest_path = (char *)malloc(PATH_MAX);
//    CFURLGetFileSystemRepresentation(manifest_url, true, (uint8_t *)manifest_path, PATH_MAX);
//    
//    if (manifest_url != NULL)
//        {
//          CFRelease(manifest_url);
//        }
//    return manifest_path;
//}

char* GetPath_Apple_dir(CFStringRef name, CFStringRef type)
{
    CFURLRef manifest_url = CFBundleCopyResourceURL(CFBundleGetMainBundle(),
                                                    CFSTR("resources/scenes"), NULL,
                                                    NULL);
    
//    CFURLRef dir_url = CFBundleCopyResourceURL(CFBundleGetMainBundle(),
//                                               CFSTR("MyFolder"), // имя папки
//                                               NULL,              // расширение = NULL
//                                               NULL);
    
    char * manifest_path = (char *)malloc(PATH_MAX);
    CFURLGetFileSystemRepresentation(manifest_url, true, (uint8_t *)manifest_path, PATH_MAX);
    
    if (manifest_url != NULL)
        {
          CFRelease(manifest_url);
        }
    return manifest_path;
}


char* GetPath(const std::string& title, const std::string* type)
{
#ifdef __APPLE__
    CFStringRef p_name = CFStringCreateWithCString(NULL, title.c_str(), NULL);
    CFStringRef p_type = type? CFStringCreateWithCString(NULL, type->c_str(), NULL) : NULL;
    
  //  if( type)
        return GetPath_Apple(p_name, p_type);
  //  else
   //     return GetPath_Apple_dir(p_name, p_type);
#endif
    return NULL;
}
