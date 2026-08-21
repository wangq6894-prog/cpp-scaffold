/*日志标准输出
    1.包含头文件<spdlog/spdlog.h>
    2.创建日志对象
    3.设置日志输出等级
    4.设置日志输出格式
    5.输出日志
*/
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <iostream>
int main(int argc, char* argv[]){
    //auto logger = spdlog::stdout_color_mt("stdout_logger");
    //auto logger = spdlog::basic_logger_mt("file_logger","./file.logs");
    auto logger = spdlog::rotating_logger_mt("file_logger","./rotating.dat",1024,3);

    for(int i = 0;i < 10000;i++){
        logger->error("hello world - {}",i);
    }

    logger->set_level(spdlog::level::err);
    logger->set_pattern("[%Y-%m-%d %H:%M][%-7l] %v");
    logger->debug("{}今年{}岁","张三",18);
    logger->info("{}今年{}岁","李四",19);
    logger->warn("{}今年{}岁","王五",20);
    logger->error("{}今年{}岁","赵六",21);
    logger->critical("{}今年{}岁","王二",22);
}
