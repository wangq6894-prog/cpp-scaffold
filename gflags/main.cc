//gflags使用:

//1. 引入头文件
#include <gflags/gflags.h>
#include <iostream>
#include <string>
#include "child.h"
using namespace std;
//2.定义要捕获的参数信息，以及设置静默值
DEFINE_bool(reuse_addr,true,"启用地址重用选项");
DEFINE_int32(listen_port,8080,"服务器监听端口");
DEFINE_string(listen_ip,"0,0,0,0","服务器监听IP");
DEFINE_double(pi,3.14,"圆周率");
int main(int argc, char* argv[]){
    //3.解析参数，初始化参数
    gflags::ParseCommandLineFlags(&argc,&argv,true);
    //4.访问参数
    cout<<"reuse_addr:"<<FLAGS_reuse_addr<<endl;
    cout<<"listen_port:"<<FLAGS_listen_port<<endl;
    cout<<"listen_ip:"<<FLAGS_listen_ip<<endl;
    cout<<"pi:"<<FLAGS_pi<<endl;

    print();

    return 0;
}