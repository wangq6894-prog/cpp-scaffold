#include "mylog.h"
namespace mylog
{
    std::shared_ptr<spdlog::logger> g_logger;
    void mylog_init(const log_setting& setting)
    {
        //1.判断日志器类型        
        //2.判断输出目标
        //3.创建日志器
        if(setting.async == true){
            //异步日志器
            if(setting.path == "stdout"){
                g_logger = spdlog::stdout_color_mt<asynclog::async_factory>("stdout_logger");
            }else{
                g_logger = spdlog::basic_logger_mt<asynclog::async_factory>("file_logger",setting.path);
            }
        }else{
            //同步日志器
            if(setting.path == "stdout"){
                g_logger = spdlog::stdout_color_mt("stdout_logger");
            }else{
                g_logger = spdlog::basic_logger_mt("file_logger",setting.path);
            }
        }
        //4.设置日志等级
        g_logger->set_level(spdlog::level::level_enum(setting.level));
        //5.设置日志格式
        g_logger->set_pattern(setting.format);
    }
}