//
//  GetPath.cpp
//  Labirint
//
//  Created by marina porkhunova on 07.01.2023.
//

#include "GetPath.hpp"




// ________APPLE REALISATION________
#ifdef __APPLE__
#include <mach-o/dyld.h>

fs::path GetExecutablePath()
{
    char buffer[PATH_MAX];
    uint32_t size = sizeof(buffer);
    if (_NSGetExecutablePath(buffer, &size) == 0) {
        return fs::path(buffer);
    }
    return {};
}

fs::path GetResourcePathFromApple()
{
#ifdef DEBUG
    fs::path exePath = GetExecutablePath();

    // up to project root (Debug: Build/Products/Debug/ -> project)
    fs::path candidate = exePath;
    for (int i = 0; i < 8; ++i) {
        candidate = candidate.parent_path();
        if (fs::exists(candidate / "Build")) {
            break;// up to Build folder
        }
    }

    if (fs::exists(candidate / "resources")) {
        return candidate / "resources";
    }
    // fallback
    return exePath.parent_path();
#else // RELEASE
    // take Resources from .app bundle
    CFURLRef resURL = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
    char buffer[PATH_MAX];
    if (resURL) {
        if (CFURLGetFileSystemRepresentation(resURL, true, (UInt8*)buffer, PATH_MAX)) {
            CFRelease(resURL);
            return fs::path(buffer);
        }
        CFRelease(resURL);
    }
    return fs::current_path();
#endif // DEBUG or RELEASE
}

#endif //__APPLE__
// ________END OF APPLE REALISATION________


fs::path GetResourcePath()
{
#ifdef __APPLE__
    return GetResourcePathFromApple();
#endif //__APPLE__
    return {}; // mayby someday
}

#include <filesystem>
#include <cstdlib>
#include <iostream>

fs::path GetSavePath() {
#ifdef __APPLE__
    const char* home = std::getenv("HOME");
    std::filesystem::path savePath = std::string(home) + "/Library/Application Support/EPet";
    std::filesystem::create_directories(savePath);
    return savePath;
    
#endif //__APPLE__
    return {}; // mayby someday
}
