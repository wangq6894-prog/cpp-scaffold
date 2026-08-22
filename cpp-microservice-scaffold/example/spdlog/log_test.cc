#include <mylog.h>
#include <gflags/gflags.h>
//1.通过gflags定义要捕获的参数
DEFINE_bool(log_async,true,"是否异步日志器");
DEFINE_int32(log_level,1,"日志等级");
DEFINE_string(log_format,"[%H:%M:%S][%-7l] %v","日志格式");
DEFINE_string(log_path,"stdout","日志输出目标(文件路径或标准输出)");

//4.测试日志输出

int main(int argc,char* argv[]){
    //2.解析命令行参数
    google::ParseCommandLineFlags(&argc,&argv,true);
    //3.初始化日志器参数配置结构
    mylog::log_setting settings = {
        .async = FLAGS_log_async,
        .level = FLAGS_log_level,
        .format = FLAGS_log_format,
        .path = FLAGS_log_path,
    };
    //4.初始化日志器
    mylog::mylog_init(settings);
    //5.输出日志
    DBG("{}今年{}岁","张三",114);
    INF("{}今年{}岁","李四",19);
    WRN("{}今年{}岁","王五",20);
    ERR("{}今年{}岁","赵六",21);
    DBG("这是一个调试日志");
    return 0;
}