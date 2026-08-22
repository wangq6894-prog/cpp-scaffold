/*
    util细碎工具封装
        1.json序列化和反序列化
*/

#pragma once
#include <jsoncpp/json/json.h>
#include <iostream>
#include <memory>
#include <optional>
#include <sstream>

namespace myutil {
class JSON {
   public:
    static std::optional<std::string> serialize(const Json::Value& val);
    static std::optional<Json::Value> deserialize(const std::string& input);
};
}  // namespace myutil