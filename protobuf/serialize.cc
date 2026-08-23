/*
    序列化和反序列化操作
    1.编写接口描述语言，进行数据结构描述
    2.堆proto文件进行编译，生成对应的代码文件
    3.包含头文件
    4.进行序列化和反序列化操作
        
    5.进行数据交互
*/
#include "person.pb.h"
#include <google/protobuf/util/json_util.h>
std::string serialize_test(){
       person::Student stu;
    stu.set_name("zhangsan");
    stu.set_sn(114514);
    stu.set_sex(person::man);
    stu.add_score(99);
    auto score = stu.mutable_score();
    score->Add(88);
    auto other = stu.mutable_other();
    (*other)[0] = "abc";
    other->insert({1,"def"});

    auto str = stu.SerializeAsString();
    std::cout << str << std::endl;
    return str;
}

void deserialize_test(const std::string& str){
    person::Student stu;
    bool ret = stu.ParseFromString(str);
    if(ret == false){
        std::cout << "deserialize failed" << std::endl;
        return;
    }
    std::cout << stu.sn() << std::endl;
    std::cout << stu.name() << std::endl;
    std::cout << stu.sex() << std::endl;
    int sz = stu.score_size();
    std::cout << sz << std::endl;
    for(int i = 0; i < sz; i++){
        std::cout << stu.score(i) << std::endl;
    }
    for(auto it : stu.other()){
        std::cout << it.first <<" "<< it.second << std::endl;
    }
}

void json2pb_test(){
    std::string json_str = R"({"sn": 114514,"name": "zhangsan","sex": 0,"score": [99, 88],"other": {"1": "abc","2": "def"}})";

    person::Student stu;
    auto ret = google::protobuf::util::JsonStringToMessage(json_str, &stu);
    if(ret.ok() == false){
        std::cout << "json2pb failed" << ret.ToString() << std::endl;
        return;
    }
    std::cout << stu.sn() << std::endl;
    std::cout << stu.name() << std::endl;
    std::cout << stu.sex() << std::endl;
    int sz = stu.score_size();
    std::cout << sz << std::endl;
    for(int i = 0; i < sz; i++){
        std::cout << stu.score(i) << std::endl;
    }
    for(auto it : stu.other()){
        std::cout << it.first <<" "<< it.second << std::endl;
    }
}

void pb2json_test(){
    person::Student stu;
    stu.set_name("zhangsan");
    stu.set_sn(114514);
    stu.set_sex(person::man);
    stu.add_score(99);
    stu.add_score(88);
    auto other = stu.mutable_other();
    (*other)[0] = "abc";
    other->insert({1,"def"});
    other->insert({2,"ghi"});
    std::string json_str;
    google::protobuf::util::JsonPrintOptions options;
    options.add_whitespace = true;
    auto ret = google::protobuf::util::MessageToJsonString(stu, &json_str, options);
    if(ret.ok() == false){
        std::cout << "pb2json failed" << ret.ToString() << std::endl;
        return;
    }
    std::cout << json_str << std::endl;
}
int main(){
    auto str = serialize_test();
    deserialize_test(str);
    std::cout << "======================" << std::endl;
    json2pb_test();
    std::cout << "======================" << std::endl;
    pb2json_test();
    return 0;
}