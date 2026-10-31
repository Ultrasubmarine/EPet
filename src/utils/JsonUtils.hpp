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
    ReadResult ReadValueImpl(const json& from, const std::string& path, T& out, std::source_location loc)
    {
        const json::json_pointer ptr(path);
        if (!from.contains(ptr)) {
            return ReadResult::NoField;
        }
        
        try {
            out = from[ptr].get<T>();
        }
        catch (const json::exception& e) {
            LOG_WARNING_AT(loc, "Field [" << path << "] has wrong type. Use default: " << e.what());
            return ReadResult::WrongType;
        }
        return ReadResult::Success;
    }
}

/// path - json pointer, e.g. "/window/screen/width". out is untouched on failure
template<class T>
bool ReadValue(const json& from, const std::string& path, T& out, std::source_location loc = std::source_location::current())
{
    auto result = detail::ReadValueImpl(from, path, out, loc);
    
    switch (result) {
        case detail::ReadResult::Success: {
            return true;
        }
        case detail::ReadResult::NoField: {
            LOG_WARNING_AT(loc, "Field [" << path << "] not found. Use default");
            return false;
        }
        case detail::ReadResult::WrongType: {
            return false;
        }
    }
}

/// path - json pointer, e.g. "/window/screen/width". out is untouched on failure
template<class T>
bool ReadOptionalValue(const json& from, const std::string& path, T& out, std::source_location loc = std::source_location::current())
{
    return detail::ReadValueImpl(from, path, out, loc) == detail::ReadResult::Success;
}

template<class T>
bool WriteValue(json& to, const std::string& path, const T& value,std::source_location loc = std::source_location::current())
{
    try {
        const json::json_pointer ptr(path);
        to[ptr] = value;
    }
    catch (const json::exception& e) {
        LOG_ERROR_AT(loc, "Failed to write field [" << path << "]: " << e.what());
        return false;
    }
    return true;
}

#endif /* JsonUtils_hpp */
