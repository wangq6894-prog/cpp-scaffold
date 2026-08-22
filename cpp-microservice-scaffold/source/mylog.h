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
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
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
}
    //生成日志输出宏
    #define FMT_PREFIX std::string("[{}:{}]:")
    #define DBG(fmt,...) mylog::g_logger->debug(FMT_PREFIX+fmt,__FILE__,__LINE__,##__VA_ARGS__)
    #define INF(fmt,...) mylog::g_logger->info(FMT_PREFIX+fmt,__FILE__,__LINE__,##__VA_ARGS__)
    #define WRN(fmt,...) mylog::g_logger->warn(FMT_PREFIX+fmt,__FILE__,__LINE__,##__VA_ARGS__)
    #define ERR(fmt,...) mylog::g_logger->error(FMT_PREFIX+fmt,__FILE__,__LINE__,##__VA_ARGS__)
