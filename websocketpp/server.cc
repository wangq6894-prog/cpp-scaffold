/*
使用websocketpp库搭建服务器：
  0. 编写各个事件的回调处理函数
  1. 先实例化服务器对象
  2. 向服务器对象注册回调函数：握手成功，连接断开，收到websocket消息，收到http请求
  3. 初始化asio框架
  4. 启动地址重用
  5. 设置监听地址
  6. 开启获取新连接
  7. 启动服务器
*/

#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <functional>
#include <iostream>

typedef websocketpp::server<websocketpp::config::asio> websocketsvr_t;

void onOpen(websocketsvr_t* server, websocketpp::connection_hdl hdl){
    std::cout << "websocket握手成功" << std::endl;
}
void onClose(websocketsvr_t* server, websocketpp::connection_hdl hdl){
    std::cout << "websocket连接断开" << std::endl;
}
void onMessage(websocketsvr_t* server, websocketpp::connection_hdl hdl, websocketsvr_t::message_ptr message){
    //websocket协议通过http协议切换过来，所有connection中保存了http的信息
    auto conn = server->get_con_from_hdl(hdl);
    const auto &request = conn -> get_request();    
    std::cout << request.get_method() << std::endl;
    std::cout << request.get_uri() << std::endl;
    auto headers = request.get_headers();
    for (auto &header : headers) {
        std::cout << header.first << "：" << header.second << std::endl;
    }
    std::cout << "收到websocket消息：" << message->get_payload() << std::endl;
    //回复消息
    conn->send("回显：" + message->get_payload(),websocketpp::frame::opcode::text);
}
void onHttp(websocketsvr_t* server, websocketpp::connection_hdl hdl){
    //1.获取连接对象
    auto conn = server->get_con_from_hdl(hdl);
    //2.打印请求信息，请求方法，URI，正文，请求头
    const auto &request = conn -> get_request();    
    std::cout << "请求方法：" << request.get_method() << std::endl;
    std::cout << "请求URI：" << request.get_uri() << std::endl;
    std::cout << "请求正文：" << request.get_body() << std::endl;
    std::cout << "请求头：" << std::endl;
    for (auto &header : request.get_headers()) {
        std::cout << header.first << "：" << header.second << std::endl;
    }
    //3.构建响应
    conn->set_status(websocketpp::http::status_code::value::ok);
    conn->set_body("<html><body><h1>Hello, World!</h1></body></html>");
    conn->append_header("Content-Type", "text/html");
}
int main(int argc,char* argv[]){
    //1. 先实例化服务器对象
    websocketsvr_t server;
    //1.5禁用日志
    server.clear_access_channels(websocketpp::log::alevel::all);
    //2. 向服务器对象注册回调函数：握手成功，连接断开，收到websocket消息，收到http请求
    server.set_open_handler(std::bind(onOpen, &server, std::placeholders::_1));
    server.set_close_handler(std::bind(onClose, &server, std::placeholders::_1));
    server.set_message_handler(std::bind(onMessage, &server, std::placeholders::_1, std::placeholders::_2));
    server.set_http_handler(std::bind(onHttp, &server, std::placeholders::_1));
    //3. 初始化asio框架
    server.init_asio();
    //4. 启动地址重用
    server.set_reuse_addr(true);
    //5. 设置监听地址
    server.listen(9000);
    //6. 开启获取新连接
    server.start_accept();
    //7. 启动服务器
    server.run();
    return 0;
}