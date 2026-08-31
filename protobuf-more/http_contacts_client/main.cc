#include <iostream>
#include "httplib.h"
#include "ContactsException.h"
#include "add_contact.pb.h"

using namespace std;
using namespace httplib;

#define CONTACTS_HOST "139.159.150.152"
#define CONTACTS_PORT 8123

void addContact();


void menu() {
    std::cout << "-----------------------------------------------------" << std::endl
            << "--------------- 请选择对通讯录的操作 ----------------" << std::endl
            << "------------------ 1、新增联系⼈ --------------------" << std::endl 
            << "------------------ 2、删除联系⼈ --------------------" << std::endl
            << "------------------ 3、查看联系⼈列表 ----------------" << std::endl 
            << "------------------ 4、查看联系⼈详细信息 ------------" << std::endl
            << "------------------ 0、退出 --------------------------" << std::endl
            << "-----------------------------------------------------" << std::endl;
}


int main() {
    enum OPTION {QUIT=0, ADD, DEL, FIND_ALL, FIND_ONE};
    while (true) {
        menu();
        cout << "--->请选择：" ;
        int choose;
        cin >> choose;
        cin.ignore(256, '\n');
        try {
            switch (choose) {
                case OPTION::QUIT:
                    cout << "--->程序退出" << endl;
                    return 0;
                case OPTION::ADD:
                    addContact();
                    break;
                case OPTION::DEL:
                case OPTION::FIND_ALL:
                case OPTION::FIND_ONE:
                    break;
                default:
                    cout << "选择有误，请重新选择!" << endl;
                    break;
            }
        } catch (const ContactsException& e) {
            cout << "--->操作通讯录时发生异常" << endl
                  << "--->异常信息：" << e.what() << endl;
        }

    }
    

    return 0;
}

void buildAddContactRequest(add_contact::AddContactRequest* req) {
    cout << "请输入联系人姓名：";
    string name;
    getline(cin, name);
    req->set_name(name);

    cout << "请输入联系人年龄：";
    int age;
    cin >> age;
    req->set_age(age);
    cin.ignore(256, '\n');

    for (int i = 0;; i++) {
        cout << "请输入联系人电话" << i+1 << "(只输⼊回⻋完成电话新增):";
        string number;
        getline(cin, number);
        if (number.empty()) {
            break;
        }
        add_contact::AddContactRequest_Phone* phone = req->add_phone();
        phone->set_number(number);

        cout << "请输入该电话类型(1、移动电话   2、固定电话): ";
        int type;
        cin >> type;
        cin.ignore(256, '\n');
        switch (type) {
            case 1:
                phone->set_type(add_contact::AddContactRequest_Phone_PhoneType::AddContactRequest_Phone_PhoneType_MP);
                break;
            case 2:
                phone->set_type(add_contact::AddContactRequest_Phone_PhoneType::AddContactRequest_Phone_PhoneType_TEL);
                break;
            default:
                cout << "选择有误！" << endl;
                break;
        }
    }
}


void addContact() {
    Client cli(CONTACTS_HOST, CONTACTS_PORT);

    // 构造 req
    add_contact::AddContactRequest req;
    buildAddContactRequest(&req);

    // 序列化 req
    string req_str;
    if (!req.SerializeToString(&req_str)) {
        throw ContactsException("AddContactRequest序列化失败!");
    }

    // 发起post调用
    auto res = cli.Post("/contacts/add", req_str, "application/protobuf");
    if (!res) {
        string err_desc;
        err_desc.append("/contacts/add 链接失败！错误信息：")
                .append(httplib::to_string(res.error()));
        throw ContactsException(err_desc);
    } 

    // 反序列化 resp
    add_contact::AddContactResponse resp;
    bool parse = resp.ParseFromString(res->body);
    if (res->status != 200 && !parse) {
        string err_desc;
        err_desc.append("/contacts/add 调用失败") 
                .append(std::to_string(res->status))
                .append("(").append(res->reason).append(")");
        throw ContactsException(err_desc);
    } else if (res->status != 200) {
        string err_desc;
        err_desc.append("/contacts/add 调用失败") 
                .append(std::to_string(res->status))
                .append("(").append(res->reason).append(") 错误原因：")
                .append(resp.error_desc());
        throw ContactsException(err_desc);
    } else if (!resp.success()) {
        string err_desc;
        err_desc.append("/contacts/add 结果异常") 
                .append("异常原因：")
                .append(resp.error_desc());
        throw ContactsException(err_desc);
    }

    // 结果打印
    cout << "新增联系人成功,联系人ID: " << resp.uid() << endl;
}