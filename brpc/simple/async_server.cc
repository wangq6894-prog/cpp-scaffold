#include <brpc/server.h>
#include "cal.pb.h"
#include <thread>
#include <chrono>
#include <iostream>

class CalServiceImpl : public cal::CalService{
public:
    CalServiceImpl(){}
    ~CalServiceImpl(){}
    virtual void Add(google::protobuf::RpcController* controller,const ::cal::AddReq* request,::cal::AddRsp* response,::google::protobuf::Closure* done) override {
        std::thread thr([=](){
            std::this_thread::sleep_for(std::chrono::seconds(3));
            std::cout << "Add" << std::endl;
            brpc::ClosureGuard guard(done);//当done_guard被释放的时候执行done->Run()来完成本次调用
            int result = request -> num1() + request -> num2();
            response -> set_result(result);
        });
        thr.detach();
        std::cout << "=========" << std::endl;
    };
};

int main(int argc,char* argv[]){
    // 1. 实例化计算服务对象
    CalServiceImpl cal_service;
    // 2. 定义服务器配置对象
    brpc::ServerOptions options;
    options.idle_timeout_sec = -1;//空闲不删除
    // 3. 实例化服务器对象
    brpc::Server server;
    // 4.添加服务
    int ret = server.AddService(&cal_service,brpc::SERVER_DOESNT_OWN_SERVICE);
    if(ret == -1){
        std::cerr << "AddService failed,ret:" << ret << std::endl;
        return -1;
    }
    // 5. 启动服务器
    ret = server.Start(9000,&options);
    if(ret == -1){
        std::cerr << "Start failed,ret:" << ret << std::endl;
        return -1;
    }
    // 6. 等待服务器停止
    server.RunUntilAskedToQuit();
    // if(ret == -1){
    //     std::cerr << "RunUntilAskedToQuit failed,ret:" << ret << std::endl;
    //     return -1;
    // }
    return 0;
}