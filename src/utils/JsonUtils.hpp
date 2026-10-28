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

namespace detail {
    
    enum class ReadResult
    {
        Success,
        WrongType,
        NoField,
    };

    template<class T>
    ReadResult ReadValueImpl(const json& from, const std::string& path, T& out)
    {
        const json::json_pointer ptr(path);
        if (!from.contains(ptr)) {
            return ReadResult::NoField;
        }
        
        try {
            out = from[ptr].get<T>();
        }
        catch (const json::exception& e) {
            LOG_WARNING("Field [" << path << "] has wrong type. Use default: " << e.what());
            return ReadResult::WrongType;
        }
        return ReadResult::Success;
    }
}

/// path - json pointer, e.g. "/window/screen/width". out is untouched on failure
template<class T>
bool ReadValue(const json& from, const std::string& path, T& out)
{
    auto result = detail::ReadValueImpl(from, path, out);
    
    switch (result) {
        case detail::ReadResult::Success: {
            return true;
        }
        case detail::ReadResult::NoField: {
            LOG_WARNING("Field [" << path << "] not found. Use default");
            return false;
        }
        case detail::ReadResult::WrongType: {
            return false;
        }
    }
}

/// path - json pointer, e.g. "/window/screen/width". out is untouched on failure
template<class T>
bool ReadOptionalValue(const json& from, const std::string& path, T& out)
{
    return detail::ReadValueImpl(from, path, out) == detail::ReadResult::Success;
}

#endif /* JsonUtils_hpp */
