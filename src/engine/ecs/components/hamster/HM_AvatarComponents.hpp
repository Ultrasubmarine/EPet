//
//  HM_AvatarComponents.hpp
//  EPet
//
//  Created by marina porkhunova on 25.09.2026.
//

#ifndef HM_AvatarComponents_hpp
#define HM_AvatarComponents_hpp

#include <string>

#include "json.hpp"

using json = nlohmann::json;

struct Avatar /// not saved: no saver registered
{
    int level = -1; /// -1 - avatar wasn't applied yet
    std::string tag;

    static Avatar Load(const json& data) { return {}; }
};

#endif /* HM_AvatarComponents_hpp */
