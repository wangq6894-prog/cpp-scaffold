#include "../../source/util.h"

void seriable_test(){
    Json::Value val;
    val["name"] = "ww";
    val["age"] = 18;
    val["score"].append(90.0);
    val["score"].append(80.0);
    val["score"].append(70.0);
    auto ret = myutil::JSON::serialize(val);
    if(!ret){
        return;
    }
    std::cout << *ret << std::endl;
}
void deserialize_test(){
    std::string str = R"({"name":"zhangsan","age":18,"score":[114,514,191]})";
    auto ret = myutil::JSON::deserialize(str);
    if(!ret){
        return;
    }
    std::cout << (*ret)["name"].asString() << std::endl;
    std::cout << (*ret)["age"].asInt() << std::endl;
    if (!(*ret)["score"].isNull() && (*ret)["score"].isArray()) {
        int sz = (*ret)["score"].size();
        for (int i = 0; i < sz; i++) {
            std::cout << (*ret)["score"][i].asDouble() << std::endl;
        }
    }
}
int main(){
    seriable_test();
    deserialize_test();
    return 0;
}