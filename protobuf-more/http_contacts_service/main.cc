#include <iostream>
#include "httplib.h"
#include "add_contact.pb.h"

using namespace std;
using namespace httplib;

class ContactsException
{
private:
  std::string message;
public:
  ContactsException(std::string str = "A problem") : message(str) {}
  std::string what() const {
      return message;
  }
};

void printContact(add_contact::AddContactRequest &req) {
    cout << "联系人姓名：" << req.name() << endl;
    cout << "联系人年龄：" << req.age() << endl;
    for (int j = 0; j < req.phone_size() ; j++) {
        const add_contact::AddContactRequest_Phone& phone = req.phone(j);
        cout << "联系人电话" << j+1 << ":" << phone.number();
        // 联系人电话1:1311111  (MP)
        cout << "   (" << phone.PhoneType_Name(phone.type()) << ")" <<endl;
    }
}

 static unsigned int random_char() {
    // ⽤于随机数引擎获得随机种⼦
    std::random_device rd; 
    // mt19937是c++11新特性，它是⼀种随机数算法，⽤法与rand()函数类似，但是mt19937具有速度快，周期⻓的特点
    // 作⽤是⽣成伪随机数
    std::mt19937 gen(rd()); 
    // 随机⽣成⼀个整数i 范围[0, 255]
    std::uniform_int_distribution<> dis(0, 255);
    return dis(gen);
 }

 // ⽣成 UUID （通⽤唯⼀标识符）
 static std::string generate_hex(const unsigned int len) {
    std::stringstream ss;
    // ⽣成 len 个16进制随机数，将其拼接⽽成
    for (auto i = 0; i < len; i++) {
        const auto rc = random_char();
        std::stringstream hexstream;
        hexstream << std::hex << rc;
        auto hex = hexstream.str();
        ss << (hex.length() < 2 ? '0' + hex : hex);
    }
    return ss.str();
 }


int main() {
    cout << "-----------服务启动----------" << endl;
    Server server;

    server.Post("/contacts/add", [](const Request& req, Response& res) {
        cout << "接收到post请求!" << endl; 
        // 反序列化 request: req.body
        add_contact::AddContactRequest request;
        add_contact::AddContactResponse response;
        try {
            if (!request.ParseFromString(req.body)) {
              throw ContactsException("AddContactRequest反序列化失败!");
            }

            // 新增联系人，持久化存储通讯录----》 打印新增的联系人信息
            printContact(request);

            // 构造 response：res.body
            response.set_success(true);
            response.set_uid(generate_hex(10));

            // res.body (序列化response)
            string response_str;
            if (!response.SerializeToString(&response_str)) {
                throw ContactsException("AddContactResponse序列化失败!");
            }
            res.status = 200;
            res.body = response_str;
            res.set_header("Content-Type", "application/protobuf");

        } catch (const ContactsException& e) {
            res.status = 500;
            response.set_success(false);
            response.set_error_desc(e.what());
            string response_str;
            if (response.SerializeToString(&response_str)) {
                res.body = response_str;
                res.set_header("Content-Type", "application/protobuf");
            }
            cout << "/contacts/add 发生异常，异常信息：" << e.what() << endl;
        }


    });
    
    // 绑定 8123 端口，并且将端口号对外开放
    server.listen("0.0.0.0", 8123);
    return 0;
}