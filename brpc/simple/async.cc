#include <brpc/channel.h>
#include "cal.pb.h"
#include <iostream>

void Callback(brpc::Controller* cntl,cal::AddReq* request,cal::AddRsp* response){
    std::unique_ptr<brpc::Controller> cntl_guard(cntl);
    std::unique_ptr<cal::AddReq> req_guard(request);
    std::unique_ptr<cal::AddRsp> rsp_guard(response);
    if(cntl->Failed() == true){
        std::cout << "rpc请求失败：" << cntl->ErrorText() << std::endl;
        return;
    }
    std::cout << response->result() << std::endl;
}

int main(int argc,char* argv[]){
    //0.实例化ChannelOptions对象
    brpc::ChannelOptions options;
    options.protocol = "baidu_std";
    //1.实例化Channel对象
    brpc::Channel channel;
    channel.Init("192.168.8.128:9000",&options);
    //2.实例化CalService_stub对象--用于发起rpc请求
    cal::CalService_Stub stub(&channel);
    brpc::Controller* cntl = new brpc::Controller();
    cal::AddReq* request = new cal::AddReq();
    cal::AddRsp* response = new cal::AddRsp();
    request->set_num1(10);
    request->set_num2(20);
    google::protobuf::Closure* closure = brpc::NewCallback(Callback,cntl,request,response);
    stub.Add(cntl,request,response,closure);
    std::cout << "===========" << std::endl;
    getchar();
    return 0;
}