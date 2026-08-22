//序列化json字符串
#include <jsoncpp/json/json.h>
#include <iostream>
#include <sstream>

int main(){
    Json::Value val;
    val["name"] = "zhangsan";
    val["age"] = 18;
    val["score"].append(114);
    val["score"].append(514);
    val["score"].append(191);
    //1.实例化建造者对象
    //2.通过建造者对象构造序列化对象
    //3.通过序列化对象进行序列化
    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    //builder["indentation"] = "";
    std::unique_ptr<Json::StreamWriter> swp(builder.newStreamWriter());
    std::stringstream ss;
    int ret = swp -> write(val,&ss);
    if(ret != 0){
        std::cout << "write failed" << std::endl;
        return -1;
    }
    std::string str = ss.str();
    std::cout << str << std::endl;
    return 0;
}