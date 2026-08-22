/*日志操作封装
    1.防止头文件重复包含    
    2.包含头文件
    3.声名命名空间
    4.声名全局日志器
    5.声名日志配置结构体
    6.声名全局日志器初始化接口
    7.封装日志输出宏
*/
#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sinks.h>
#include <spdlog/sinks/rotating_file_sinks.h>
#include <spdlog/async.h>
//声名命名空间
namespace mylog
{
    //声名日志配置结构体
    struct log_setting{
        bool async;
        int level;
        std::string format;
        std::string path;//日志输出目标(文件路径或标准输出)
    };
    //声名全局日志器
    extern std::shared_ptr<spdlog::logger> g_logger;
    //声名全局日志器初始化接口
    extern void mylog_init(const log_setting& setting);
    //生成日志输出宏
    DBG(fmt,...) g_logger->debug("[{}:{}]:"+fmt,__FILE__,__LINE__,##__VA_ARGS__)
    INF(fmt,...) g_logger->info("[{}:{}]:"+fmt,__FILE__,__LINE__,##__VA_ARGS__)
    WRN(fmt,...) g_logger->warn("[{}:{}]:"+fmt,__FILE__,__LINE__,##__VA_ARGS__)
    FATAL(fmt,...) g_logger->fatal("[{}:{}]:"+fmt,__FILE__,__LINE__,##__VA_ARGS__)
}
