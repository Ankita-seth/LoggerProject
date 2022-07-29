#include "Logger.h"

LoggerClass::Logger* LoggerClass::LoggerFactory::CreateFileLogger(string FilePath)
{
    return nullptr;


}

LoggerClass::Logger* LoggerClass::LoggerFactory::CreateConsoleLogger()
{
    return nullptr;
}

ostream& LoggerClass::ConsoleLogger::GetStream()
{
    return GetStream();
}

ostream& LoggerClass::FileLogger::GetStream()
{
    return GetStream();
}
