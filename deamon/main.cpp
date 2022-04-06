#include <QCoreApplication>
#include <gflags/gflags.h>
#include <iostream>

//https://blog.csdn.net/jcjc918/article/details/50876613?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_default&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_default&utm_relevant_index=2
//https://blog.csdn.net/u013066730/article/details/84103083

#define DEAMON_VERSION "V1.0"

DEFINE_string(name, "zhang san", "your name");
DEFINE_int32(age, 18, "your age");

//检查参数
static bool ValidateAge(const char* flagname, int32_t value)
{
        if (value > 0 && value < 200)
            return true;
        printf("Invalid value for --%s: %d\n", flagname, (int)value);
        return false;
}

int main(int argc, char *argv[])
{

    //QCoreApplication a(argc, argv);

    //设置版本信息 deamon.exe -version
    gflags::SetVersionString(DEAMON_VERSION);
    //帮助信息 deamon.exe -help
    gflags::SetUsageMessage("command line brew\n"
          "usage: deamon <command> <args>\n\n"
          "commands:\n"
          "  name           your name\n"
          "  age            your age\n");

    gflags::ParseCommandLineFlags(&argc, &argv, true);
    static const bool port_dummy = gflags::RegisterFlagValidator(&FLAGS_age, &ValidateAge);
    std::cout << "your name is : " << FLAGS_name
            << ", your age is: " << FLAGS_age << std::endl;
    gflags::ShutDownCommandLineFlags();
    //return a.exec();
    return 0;
}
