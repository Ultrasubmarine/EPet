//
//  JsonUtils.hpp
//  EPet
//
//  Created by marina porkhunova on 14.10.2026.
//

#ifndef JsonUtils_hpp
#define JsonUtils_hpp

#include <string>

#include "json.hpp"
#include "Logger.hpp"

using json = nlohmann::json;

/// path - json pointer, e.g. "/window/screen/width". out is untouched on failure
template<class T>
bool ReadValue(const json& from, const std::string& path, T& out)
{
    const json::json_pointer ptr(path);
    if (!from.contains(ptr)) {
        LOG_WARNING("[" << path << "] not found. use default");
        return false;
    }

    try {
        out = from[ptr].get<T>();
    }
    catch (const json::exception& e) {
        LOG_WARNING("[" << path << "] has wrong type. use default. " << e.what());
        return false;
    }
    return true;
}

#endif /* JsonUtils_hpp */
