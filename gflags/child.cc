#include <iostream>
#include <gflags/gflags.h>
DECLARE_string(listen_ip);
void print(){
    //5.跨文件访问数据
    std::cout<<FLAGS_listen_ip<<std::endl;
}