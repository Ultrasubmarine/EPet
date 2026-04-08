#pragma once

#include "json.hpp"
#include "Animation.hpp"

// JSON serialization for playMode as strings
// Values: "forward", "reverse", "yoyo"

NLOHMANN_JSON_SERIALIZE_ENUM(PlayMode, {
    {PlayMode::None, ""},
    {PlayMode::Forward, "Forward"},
    {PlayMode::Reverse, "Reverse"},
    {PlayMode::YoYo,    "YoYo"},
})
