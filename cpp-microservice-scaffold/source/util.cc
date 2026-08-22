#include "util.h"
#include "mylog.h"

namespace myutil {
std::optional<std::string> JSON::serialize(const Json::Value& val) {
    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    // builder["indentation"] = "";
    std::unique_ptr<Json::StreamWriter> swp(builder.newStreamWriter());
    std::stringstream ss;
    int ret = swp->write(val, &ss);
    if (ret != 0) {
        ERR("序列化失败");
        return std::nullopt;
    }
    return ss.str();
}
std::optional<Json::Value> JSON::deserialize(const std::string& input) {
    Json::CharReaderBuilder builder;
    std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    Json::Value val;
    std::string errs;
    bool ret = reader->parse(input.c_str(), input.c_str() + input.size(), &val, &errs);
    if (ret == false) {
        ERR("{} 反序列化失败: {}", input, errs);
        return std::nullopt;
    }
    std::cout << val["name"].asString() << std::endl;
    std::cout << val["age"].asInt() << std::endl;
    if (!val["score"].isNull() && val["score"].isArray()) {
        int sz = val["score"].size();
        for (int i = 0; i < sz; i++) {
            std::cout << val["score"][i].asDouble() << std::endl;
        }
    }
    return val;
}
}  // namespace myutil