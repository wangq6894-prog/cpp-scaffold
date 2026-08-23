/*
    使用httplib库搭建一个http服务器
    1.包含头文件
    2.实例化Server对象
    3.注册路由消息
    4.启动服务器
*/

#include <httplib.h>
#include <iostream>

void HelloWorld(const httplib::Request &req,httplib::Response &rsp){
    std::cout << req.method << std::endl;
    std::cout << req.path << std::endl;
    std::cout << req.body << std::endl;
    for(auto it : req.headers){
        std::cout << it.first <<" "<< it.second << std::endl;
    }
    std::string html_body = "<html><body><h1>Hello World</h1></body></html>";
    rsp.set_content(html_body, "text/html");
    rsp.set_header("Content-Type","text/html");
    rsp.status = 200;
    return;
}

int main(){
    httplib::Server svr;
    svr.Get("/hi",HelloWorld);
    svr.listen("0.0.0.0",9090);
    return 0;
}