#include <iostream>
#include <fstream>
#include "contacts.pb.h"
using namespace std;

void PrintContacts(contacts2::Contacts& contacts){
    for(int i = 0;i < contacts.contacts_size();i++){
        cout << "-----------联系人"  << i + 1 << "-----------" << endl;
        const contacts2::PeopleInfo& people = contacts.contacts(i);
        cout << "联系人姓名：" << people.name() << endl;
        cout << "联系人年龄：" << people.age() << endl;
        for(int j = 0;j < people.phone_size();j++){
            const contacts2::PeopleInfo_Phone& phone = people.phone(j);
            cout << "联系人电话 " << j + 1 << "：" << phone.number() << endl;
            cout <<"  （"<<phone.PhoneType_Name(phone.type()) <<"）"<< endl;
        }
    }
}

int main(){
    contacts2::Contacts contacts;
    //读取本地已存在的通讯录文件
    fstream input("contacts.bin",ios::in | ios::binary);
    if(!contacts.ParseFromIstream(&input)){
        cerr << "parse error" << endl;
        input.close();
        return -1;
    }
    //打印通讯录列表
    PrintContacts(contacts);
    return 0;
}