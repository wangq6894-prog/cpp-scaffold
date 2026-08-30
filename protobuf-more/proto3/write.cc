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
        contacts2::Address address;
        cout << "请输入联系人家庭地址：" << endl;
        string home_address;
        getline(cin,home_address);
        address.set_home_address(home_address);
        cout << "请输入联系人单位地址：" << endl;
        string unit_address;
        getline(cin,unit_address);
        address.set_unit_address(unit_address);
        people_info->mutable_data()->PackFrom(address);
        int other_contact;
        cout << "请输入其他联系方式（1 QQ，2 微信，其他跳过）：" << endl;
        cin >> other_contact;
        cin.ignore(256,'\n');
        if(other_contact == 1){
            cout << "请输入联系人QQ：" << endl;
            string qq;
            getline(cin,qq);
            people_info->set_qq(qq);
        }
        if(other_contact == 2){
            cout << "请输入联系人微信：" << endl;
            string wechat;
            cin >> wechat;
            people_info->set_wechat(wechat);
        }
        for(int i = 0;;i++){
            cout << "请输入联系人备注 "  << i + 1 << " 只输入回车完成备注新增" << endl;
            string remarkkey;
            getline(cin,remarkkey);
            if(remarkkey.empty()){
                break;
            }
            cout << "请输入联系人备注 "  << i + 1 << " 内容：" << endl;
            string remarkvalue;
            getline(cin,remarkvalue);
            if(remarkvalue.empty()){
                break;
            }
            people_info->mutable_remark()->insert({remarkkey,remarkvalue});
        }
        cout << "-----------添加联系人成功----------" << endl;
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