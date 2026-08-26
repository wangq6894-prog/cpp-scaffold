#include <iostream>
#include "contacts.pb.h"
#include <fstream>
using namespace std;

void AddPeopleInfo(contacts2::PeopleInfo* people_info){
    cout << "新增联系人" << endl;
    cout << "请输入联系人姓名：" << endl;
    string name;
    cin >> name;
    people_info->set_name(name);
    cout << "请输入联系人年龄：" << endl;
    int age;
    cin >> age;
    people_info->set_age(age);
    cin.ignore(256,'\n');
    cout << "添加联系人成功" << endl;
    for(int i = 0;;i++){
        cout << "请输入联系人电话 "  << i + 1 << " 只输入回车完成电话新增" << endl;
        string number;
        getline(cin,number);
        if(number.empty()){
            break;
        }
        contacts2::PeopleInfo_Phone* phone = people_info -> add_phone();
        phone->set_number(number);
        cout << "请输入改电话类型（1 移动电话 2 固定电话）：" << endl;
        int type;
        cin >> type;
        cin.ignore(256,'\n');
        switch(type){
            case 1:
                phone->set_type(contacts2::PeopleInfo_Phone_PhoneType_MP);
                break;
            case 2:
                phone->set_type(contacts2::PeopleInfo_Phone_PhoneType_TEL);
                break;
            default:
                cerr << "输入错误" << endl;
                return;
        }
           }
}

int main(){
    contacts2::Contacts contacts;
    //读取本地已存在的联系人文件
    fstream input("contacts.bin",ios::in | ios::binary);
    if(!input){
        cout<<"contacts.bin file not found,create new file"<<endl;
    }else if(contacts.ParseFromIstream(&input)){
        cerr << "parse error" << endl;
        input.close();
        return -1;
    }
    //向通讯录中添加一个联系人
    AddPeopleInfo(contacts.add_contacts());
    //将通讯录写入本地文件中
    fstream output("contacts.bin",ios::out | ios::trunc | ios::binary);
    if(!contacts.SerializeToOstream(&output)){
        cerr << "write error" << endl;
        input.close();
        output.close();
        return -1;
    }
    output.close();
}