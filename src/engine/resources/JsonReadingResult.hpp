//
//  JsonReadingResult.hpp
//  EPet
//
//  Created by marina porkhunova on 15.11.2026.
//

#ifndef JsonReadingResult_hpp
#define JsonReadingResult_hpp

enum class JsonReadingResult
{
    None,
    Success,
    NotFound,
    BrokenFile,
    OpenProblem
};

inline const char* ToString(JsonReadingResult result)
{
    switch (result) {
        case JsonReadingResult::None:        return "None";
        case JsonReadingResult::Success:     return "Success";
        case JsonReadingResult::NotFound:    return "NotFound";
        case JsonReadingResult::BrokenFile:  return "BrokenFile";
        case JsonReadingResult::OpenProblem: return "OpenProblem";
    }
    return "Unknown";
}

#endif /* JsonReadingResult_hpp */
