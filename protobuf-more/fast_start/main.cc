#include <iostream>
#include "contact.pb.h"

int main(){
    
    {
        //对一个联系人信息用PB进行序列化，并将结果打印出来
        contacts::PeopleInfo people;
        people.set_name("张珊");
        people.set_age(20);
        if(!people.SeriableToString(&people_str)){
            std::cerr << "序列化失败" << std::endl;
            return -1;
        }
        std::cout << "序列化成功，结果为：" << people_str << std::endl;
    }
    //对序列化后的内容使用PB进行反序列，解析出联系人信息并打印出来
    {
        contacts::PeopleInfo people;
        if(!people.ParseFromString(people_str)){
            std::cerr << "反序列化失败" << std::endl;
            return -1;
        }
        std::cout << "反序列化成功，结果为：" << people.name() << "，年龄为：" << people.age() << std::endl;
    }
}