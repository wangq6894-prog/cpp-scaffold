#include <jsoncpp/json/json.h>
#include <iostream>

int main(){
    Json::Value val;
    val["name"] = "zhangsan";
    val["age"] = 18;
    val["score"][0] = 114;
    val["score"][1] = 514;
    val["score"][2] = 191;
    std::string str = val.toStyledString();
    std::cout << str << std::endl;
    return 0;
}